#include "fragment53.h"
#include "src/19840.h"
#include "src/1AB70.h"
#include "src/232C0.h"
#include "src/26820.h"
#include "src/3FB0.h"
#include "src/6A40.h"
#include "src/6BC0.h"
#include "src/controller.h"
#include "src/memory.h"
#include "src/stage_loader.h"

static AssetManager* D_82A00370;
static SpriteDisplay* gSpriteDisplay;
static PokemonData gLoadedPokemon[6];

static s32 gLoadedPokemonCount = 0;

void LoadSaveSlotSprites(s32 arg0) {
    s32 i;
    unk_func_80022C28_ret* temp_v0;

    if (SaveSlot_Load(arg0) != 0) {
        temp_v0 = CreateGbsBlock(0x20, arg0, 0, 0);
        gLoadedPokemonCount = GbsBlock_ReadPokemon(gLoadedPokemon, 6, temp_v0);
        CommitAndFreeGbsBlock(temp_v0);
    }

    for (i = 0; i < gLoadedPokemonCount; i++) {
        SpriteDisplay_ConfigSlotWithAnim(gSpriteDisplay, i, &gLoadedPokemon[i], 1);
    }
}

s32 MenuStage_Frame(u8 arg0) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    func_8001ABAC(gSpriteDisplay, 0);
    Stage_BeginDisplayList();
    Gfx_FillScreen(&gDisplayListHead, 1);
    return 0;
}

void PopulateInputStructFromSprites(UnkInputStruct8000D738* arg0) {
    s32 i;
    PlayerName sp34;
    u16(*var_s1)[0x640] = arg0->unk_04[0];

    GbsGetPlayerName(&sp34);
    arg0->unk_02 = sp34.unk_00;
    arg0->unk_00 = sp34.unk_04;
    arg0->unk_03 = gLoadedPokemonCount;

    for (i = 0; i < gLoadedPokemonCount; i++, var_s1++) {
        _bcopy(SpriteDisplay_GetImagePtr(gSpriteDisplay, i), var_s1, sizeof(var_s1[0]));
    }

    if (gLoadedPokemonCount < 6) {
        bzero(var_s1, 0x4B00 + (-gLoadedPokemonCount * 0xC80));
    }
}

s32 Fragment53_Main(s32 arg0, UnkInputStruct8000D738* arg1) {
    Stage* sp24;

    main_pool_push_state('PREP');

    Gfx_InitBuffers(0x10000, 0);
    sp24 = Stage_Create(0, 1, 2, 0, 1, 1);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    FRAGMENT_LOAD(fragment31);

    D_82A00370 = AssetManager_Create(1);
    gSpriteDisplay = SpriteDisplay_Alloc(D_82A00370, 6, 0x28, 0x28);
    AssetManager_LoadArchives();
    LoadSaveSlotSprites(arg0);
    GbsEnsureBankLoaded(2);
    Stage_Set(sp24);
    Stage_AdvanceUntil(8, MenuStage_Frame);
    Stage_Destroy();
    PopulateInputStructFromSprites(arg1);
    Gfx_FreeBuffers();

    main_pool_pop_state('PREP');

    return gLoadedPokemonCount;
}
