#!/usr/bin/env python3
"""ccs.py src/file.c func [out.s]: compile only `func` (draft enabled) of src/file.c with IDO cc -S
(pre-as1 assembly, uopt register choices visible) and print that function's .s."""
import os, re, subprocess, sys
REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SCR = os.path.join(REPO, "scratch", "ccs")
os.makedirs(SCR, exist_ok=True)
src, func = sys.argv[1], sys.argv[2]
text = open(os.path.join(REPO, src)).read()
# drop GLOBAL_ASM pragmas, enable draft of func
text = re.sub(r'#pragma GLOBAL_ASM\([^)]*\)\n', '', text)
out = os.path.join(SCR, "x.c")
open(out, "w").write(text)
flags = ("-c -G 0 -non_shared -Xcpluscomm -nostdinc -Wab,-r4300_mul -DVERSION_US=1 -Iinclude -Isrc "
         "-Isrc/fragments/15 -Isrc/fragments -Isrc/libnaudio -Iassets/us -I. -Ibuild -Ilib/ultralib/include -Ilib/ultralib/include/PR "
         "-Ilib/ultralib/include/ido -Iinclude/ -woff 624,649,838,712,516,513,596,564,594 -mips2 -EB "
         "-D_MIPS_SZLONG=32 -DNDEBUG -D_FINALROM -DN_MICRO -DF3DEX_GBI_2 -DBUILD_VERSION=VERSION_I_P "
         "-DLANGUAGE_C -D_LANGUAGE_C -DNON_MATCHING -O2").split()
extra = ["-I" + os.path.dirname(src)] + (sys.argv[3:] if len(sys.argv) > 3 else [])
p = subprocess.run([os.path.join(REPO, "tools/ido/linux/7.1/cc"), "-S"] + flags + extra + [out],
                   cwd=REPO, capture_output=True, text=True)
errs = [l for l in (p.stdout + p.stderr).splitlines() if "Warning" not in l and l.strip()]
if errs:
    print("\n".join(errs[:20]))
s = open(os.path.join(REPO, "x.s")).read()
os.rename(os.path.join(REPO, "x.s"), os.path.join(SCR, "x.s"))
i = s.find("\t.ent\t%s" % func)
j = s.find("\t.end\t%s" % func, i)
print(s[i:j])
