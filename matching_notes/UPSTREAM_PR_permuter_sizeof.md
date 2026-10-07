# Upstream PR draft: decomp-permuter `sizeof(T) * N` mis-parse

Target repo: https://github.com/simonlindholm/decomp-permuter (our copy: 059609d, 2026-09-08;
upstream main was one unrelated commit ahead on 2026-10-07).
Patch: `matching_notes/permuter_sizeof_prec.patch` (touches only `perm_pycparser/c_parser.py`).

## How to file
```
cd tools/permuter
git fetch origin && git checkout -b fix-sizeof-type-prec origin/main
git apply ../../matching_notes/permuter_sizeof_prec.patch
rm perm_pycparser/yacctab.py            # tables regenerate on first parse
python3 - <<'EOF'
from perm_pycparser.c_parser import CParser
from perm_pycparser import c_generator
ast = CParser().parse("typedef int T; int f(void) { return sizeof(T) * 2 + sizeof(int) - 1; }")
print(c_generator.CGenerator().visit(ast))   # expect: return (((sizeof(T)) * 2) + (sizeof(int))) - 1;
EOF
python3 -m unittest discover -s test -t .    # needs mips-linux-gnu-gcc for test_perm
git commit -am "Parse sizeof(type) before a following binary operator"
gh pr create --fill
```
Before filing, re-check `test_perm` on a machine with `mips-linux-gnu-gcc` (we could only run the
typedef tests on Palmetto), and regenerate `yacctab.py` if upstream tracks it.

## PR title
Fix `sizeof(T) * N` being parsed as `sizeof((T) (*N))`

## PR body

`perm_pycparser` folds `cast_expression` into `unary_expression`
(`unary_expression : LPAREN type_name RPAREN unary_expression`). After
`SIZEOF LPAREN type_name RPAREN` the parser therefore has a shift/reduce conflict whenever the
next token can start a unary expression: `*`, `+`, `-`, `&`. PLY resolves it by shifting, so

```c
sp1DC = func_80005F5C(sizeof(Mtx) * 1);
```

round-trips through `import.py` as

```c
sp1DC = func_80005F5C(sizeof((Mtx) (*1)));
```

which the compiler rejects (`cfe: Error: Dereferenced a non-pointer` with IDO). The same happens
for builtin types (`sizeof(int) * 1`), so it is not a typedef-visibility issue. Stock pycparser
3.0 parses these correctly. Any source using `sizeof(T) * n` for an allocation size cannot be
imported without hand-editing.

### Fix

Split the `sizeof`/`_Alignof` type-name production out of `p_unary_expression_3` and give it a
`%prec SIZEOF_TYPE` with a new highest precedence level, so the parser reduces
`sizeof(type_name)` before shifting a following binary operator. `sizeof unary_expression` is
unchanged, as is the cast rule.

### Verification

- Grammar conflicts: 292 -> 288 shift/reduce, 191 -> 191 reduce/reduce (the four removed are
  the TIMES/PLUS/MINUS/AND lookaheads after `sizeof(type)`); no new conflicts.
- `sizeof(T) * 1`, `sizeof(T) * 10`, `10 * sizeof(T)`, `sizeof(int) * 1` now round-trip as
  written (typedef'd and builtin types).
- `test/test_deduplicate_typedefs.py` (9 tests) passes. `test/test_perm.py` could not be run in
  our environment (no `mips-linux-gnu-gcc`); it fails at `compile.sh` before parsing with or
  without this change.
- Two real-world imports (Pokemon Stadium, IDO 7.1) that previously produced an uncompilable
  `base.c` now import and permute normally.

### Notes

`c_generator.CGenerator.precedence_map` does not need updating: `SIZEOF_TYPE` is a pseudo-token
used only for conflict resolution, not an operator the generator prints.

## Diff
```diff
diff --git a/perm_pycparser/c_parser.py b/perm_pycparser/c_parser.py
index e4eadee..6cd4929 100644
--- a/perm_pycparser/c_parser.py
+++ b/perm_pycparser/c_parser.py
@@ -522,7 +522,10 @@ class CParser(PLYParser):
         ('left', 'GT', 'GE', 'LT', 'LE'),
         ('left', 'RSHIFT', 'LSHIFT'),
         ('left', 'PLUS', 'MINUS'),
-        ('left', 'TIMES', 'DIVIDE', 'MOD')
+        ('left', 'TIMES', 'DIVIDE', 'MOD'),
+        # Pseudo-token: lets `sizeof(type)` reduce before a following binary
+        # operator is shifted as the start of a cast operand (`(T) *x`).
+        ('right', 'SIZEOF_TYPE')
     )
 
     ##
@@ -1860,12 +1863,18 @@ class CParser(PLYParser):
 
     def p_unary_expression_3(self, p):
         """ unary_expression    : SIZEOF unary_expression
-                                | SIZEOF LPAREN type_name RPAREN
-                                | _ALIGNOF LPAREN type_name RPAREN
         """
+        p[0] = c_ast.UnaryOp(p[1], p[2], self._token_coord(p, 1))
+
+    def p_unary_expression_4(self, p):
+        """ unary_expression    : SIZEOF LPAREN type_name RPAREN %prec SIZEOF_TYPE
+                                | _ALIGNOF LPAREN type_name RPAREN %prec SIZEOF_TYPE
+        """
+        # Without the %prec, `sizeof(T) * 1` parses as `sizeof((T) (*1))` because
+        # this grammar folds cast_expression into unary_expression.
         p[0] = c_ast.UnaryOp(
             p[1].replace("__alignof", "_Alignof").replace("__", ""),
-            p[2] if len(p) == 3 else p[3],
+            p[3],
             self._token_coord(p, 1))
 
     def p_unary_operator(self, p):
```
