#include "battle_engine.h"
#include "src/math_util.h"

void BattleAnim_SetupStartEffects18And73Descriptor11ScatterRiseFade(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;
    Vec3s sp2C;

    Particle_GetFieldOffsetAC(arg0);
    Particle_SetScaleScaled(arg0, 0.05f);
    sp2C.x = ParticleMath_RandomRange(0x8000) - 0x4000;
    sp2C.y = ParticleMath_RandomRange(0x10000);
    sp2C.z = ParticleMath_RandomRange(0x800) - 0x400;
    Particle_AddRotationDeltaVec(arg0, sp2C);
    Particle_AddPositionFromRotationXYZAlt(arg0, ParticleMath_RandomRange(0xA));
    Particle_RotateX(arg0, 0x4000);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetPaletteIndex(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackStartEffects18And73Descriptor11ScatterRiseFade(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupStartEffects18And73Descriptor11ScatterRiseFade(arg0);
            break;

        case 2:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_ApproachScaleScaled(arg0, 1.0f, 0.05f);
    Particle_AddVelocityFromRotationXYZAlt(arg0);
}

void BattleAnim_ApplyStartEffect18MoveKeyedRadialOffset(ParticleEffectInstance* arg0) {
    f32 sp1C = 0.0f;

    switch (BattleAnim_GetOwnerSpecies(arg0->unk_10)) {
        case 0x6:
            sp1C = 15.0f;
            break;

        case 0x73:
            sp1C = 15.0f;
            break;

        case 0x87:
            sp1C = 10.0f;
            break;

        case 0x95:
            sp1C = 10.0f;
            break;

        case 0x1F:
            sp1C = 10.0f;
            break;

        case 0x22:
            sp1C = 10.0f;
            break;

        case 0x71:
            sp1C = 10.0f;
            break;
    }

    Particle_AddVelocityBackward(arg0, sp1C);
    Particle_AddVelocityRight(arg0, 5.0f);
}

void BattleAnim_SetupStartEffect18MoveKeyedRadialPulse(ParticleEffectInstance* arg0) {
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetSpeed(arg0, 0.0f);
    BattleAnim_ApplyStartEffect18MoveKeyedRadialOffset(arg0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x17);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackStartEffect18MoveKeyedRadialPulse(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupStartEffect18MoveKeyedRadialPulse(arg0);
            break;

        case 2:
            Particle_ApproachScaleScaled(arg0, 4.0f, 0.5f);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachScaleScaled(arg0, 0.1f, 0.5f);
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x20);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

void BattleAnim_SetupSharedDescriptor0FDelayedRisingColumnFade(ParticleEffectInstance* arg0) {
    s16 sp2E = Particle_GetFieldOffsetAC(arg0);
    Vec3s sp28;

    Particle_SetVelocityYScaled(arg0, 15.0f);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetSpeed(arg0, 0.0f);
    sp28.x = 0x4000 - ParticleMath_RandomRange(0x8000);
    sp28.y = sp2E << 0xD;
    sp28.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp28);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetPaletteIndex(arg0));
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackSharedDescriptor0FDelayedRisingColumnFade(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupSharedDescriptor0FDelayedRisingColumnFade(arg0);
            break;

        case 2:
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, Particle_GetFieldOffsetAC(arg0)) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleScaled(arg0, 3.0f, 0.1f);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 4:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_RotateY(arg0, 0x400);
    Particle_AddVelocityFromRotationXY(arg0);
}

void BattleAnim_SetupSharedDescriptor0FDelayedRisingColumnRandomScale(ParticleEffectInstance* arg0) {
    s16 sp2E = Particle_GetFieldOffsetAC(arg0);
    Vec3s sp28;

    Particle_SetVelocityYScaled(arg0, 15.0f);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetSpeed(arg0, MathUtil_Random_ZeroOne());
    sp28.x = 0x3000 - ParticleMath_RandomRange(0x6000);
    sp28.y = sp2E << 0xD;
    sp28.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp28);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetPaletteIndex(arg0));
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackSharedDescriptor0FDelayedRisingColumnRandomScale(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupSharedDescriptor0FDelayedRisingColumnRandomScale(arg0);
            break;

        case 2:
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, Particle_GetFieldOffsetAC(arg0)) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleScaled(arg0, 3.5f, 0.1f);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 4:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_RotateY(arg0, 0x400);
    Particle_AddVelocityFromRotationXY(arg0);
}

void BattleAnim_SetupSharedDirectionalSprayFade(ParticleEffectInstance* arg0) {
    Vec3s sp28;

    Particle_GetFieldOffsetAC(arg0);
    Particle_SetScaleScaled(arg0, 0.5f);
    Particle_SetSpeed(arg0, 0.0f);
    sp28.x = -0x4000;
    sp28.y = 0;
    sp28.z = (ParticleMath_RandomRange(0x10) << 0xB) - 0x4000;
    Particle_AddRotationDeltaVec(arg0, sp28);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetPaletteIndex(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackSharedDirectionalSprayFade(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupSharedDirectionalSprayFade(arg0);
            break;

        case 2:
            Particle_ApproachScaleScaled(arg0, 2.0f, 0.2f);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
    Particle_AddVelocityFromRotationXYZAlt(arg0);
}

void BattleAnim_SetupSharedDescriptor13DirectionalSprayScaledFade(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;
    Vec3s sp2C;

    Particle_GetFieldOffsetAC(arg0);
    Particle_SetScaleScaled(arg0, 0.5f);
    Particle_SetScaleSpeed(arg0, (MathUtil_Random_ZeroOne() * 5.0f) + 1.0f);
    Particle_SetScaleTarget(arg0, 0.2f);
    Particle_SetSpeed(arg0, MathUtil_Random_ZeroOne() * 4.0f);
    sp2C.x = -0x4000;
    sp2C.y = 0;
    sp2C.z = (ParticleMath_RandomRange(0x10) << 0xB) - 0x4000;
    Particle_AddRotationDeltaVec(arg0, sp2C);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetPaletteIndex(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackSharedDescriptor13DirectionalSprayScaledFade(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupSharedDescriptor13DirectionalSprayScaledFade(arg0);
            break;

        case 2:
            Particle_ApproachScaleTarget(arg0);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_AddVelocityFromRotationXYZAlt(arg0);
}

void BattleAnim_SetupStartEffect59EndEffect28DirectionalStreamFade(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;
    Vec3s sp2C;
    UNUSED s32 pad2[2];

    Particle_GetFieldOffsetAC(arg0);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetScaleSpeed(arg0, 1.4f);
    Particle_SetScaleTarget(arg0, 0.1f);
    MathUtil_Random_ZeroOne();
    Particle_SetSpeed(arg0, 0.0f);
    sp2C.x = -0x4000;
    sp2C.y = 0;
    sp2C.z = (ParticleMath_RandomRange(0x10) << 0xB) - 0x4000;
    Particle_AddRotationDeltaVec(arg0, sp2C);
    Particle_AddPositionFromRotationXYZAlt(arg0, 150.0f);
    Particle_AddRotationZ(arg0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetPaletteIndex(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackStartEffect59EndEffect28DirectionalStreamFade(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupStartEffect59EndEffect28DirectionalStreamFade(arg0);
            break;

        case 2:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x10);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_ApproachScaleTarget(arg0);
    Particle_AddVelocityFromRotationXYZAlt(arg0);
}

void BattleAnim_SetupUnregisteredStraightDirectionalStreamFade(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;
    Vec3s sp2C;
    UNUSED s32 pad2[2];

    Particle_GetFieldOffsetAC(arg0);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetScaleSpeed(arg0, 1.4f);
    Particle_SetScaleTarget(arg0, 0.1f);
    MathUtil_Random_ZeroOne();
    Particle_SetSpeed(arg0, 0.0f);
    sp2C.x = -0x4000;
    sp2C.y = 0;
    sp2C.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp2C);
    Particle_AddPositionFromRotationXYZAlt(arg0, 150.0f);
    Particle_AddRotationZ(arg0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetPaletteIndex(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackUnregisteredStraightDirectionalStreamFade(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupUnregisteredStraightDirectionalStreamFade(arg0);
            break;

        case 2:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x10);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_ApproachScaleTarget(arg0);
    Particle_AddVelocityFromRotationXYZAlt(arg0);
}

void BattleAnim_SetupEndEffect28Descriptor10UpwardBurstFade(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;
    Vec3f sp30;
    Vec3s sp28;

    Particle_GetFieldOffsetAC(arg0);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetScaleSpeed(arg0, 2.0f);
    Particle_SetScaleTarget(arg0, 0.1f);
    sp28.x = 0;
    sp28.y = 0;
    sp28.z = -0x8000;
    Particle_AddRotationDeltaVec(arg0, sp28);
    sp30.x = ParticleMath_RandomRange(0x64) + -50.0f;
    sp30.y = 200.0f;
    sp30.z = ParticleMath_RandomRange(0x64) + -50.0f;
    Particle_AddVelocityScaledVec(arg0, sp30);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetPaletteIndex(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackEndEffect28Descriptor10UpwardBurstFade(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupEndEffect28Descriptor10UpwardBurstFade(arg0);
            break;

        case 2:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_ApproachScaleTarget(arg0);
    Particle_AddVelocityFromRotationXYZAlt(arg0);
}

void BattleAnim_SetupEndEffect28Descriptor10WideScatterBurstFade(ParticleEffectInstance* arg0) {
    UNUSED s32 pad[4];
    Vec3s sp28;

    Particle_GetFieldOffsetAC(arg0);
    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetScaleSpeed(arg0, 2.0f);
    Particle_SetScaleTarget(arg0, 0.1f);
    sp28.x = -0x1000 - ParticleMath_RandomRange(0x6000);
    sp28.y = ParticleMath_RandomRange(0x10000);
    sp28.z = ParticleMath_RandomRange(0x800) - 0x400;
    Particle_AddRotationDeltaVec(arg0, sp28);
    Particle_AddPositionFromRotationXYZAlt(arg0, 200.0f);
    Particle_RotateX(arg0, -0x4000);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_GetPaletteIndex(arg0));
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackEndEffect28Descriptor10WideScatterBurstFade(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupEndEffect28Descriptor10WideScatterBurstFade(arg0);
            break;

        case 2:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_ApproachScaleTarget(arg0);
    Particle_AddVelocityFromRotationXYZAlt(arg0);
}

void BattleAnim_StartEffect18ScatterRadialAndColumnSequence(void) {
    BattleAnim_SpawnCategory17MarkerSlot(0x64, 1);
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x20, 3);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 3, 8, BattleAnim_CallbackStartEffects18And73Descriptor11ScatterRiseFade, &gBattleAnimParticleDescriptors[0x11], 8, 4, 2, 0, 0x25, 0);
    BattleAnim_AddSpawnDelay(0x19);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffect18MoveKeyedRadialPulse, &gBattleAnimParticleDescriptors[0x15], 0xE, 1, 2, 0, 0x25, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffect18MoveKeyedRadialPulse, &gBattleAnimParticleDescriptors[0x16], 0xE, 1, 2, 0, 0x25, 0);
    BattleAnim_SpawnDescriptor25AlphaHoldFadeOut(8, 2, 8, 0xA, 0xFF);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_CallbackSharedDescriptor0FDelayedRisingColumnFade, &gBattleAnimParticleDescriptors[0xF], 0x14, 4, 7, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_CallbackSharedDescriptor0FDelayedRisingColumnRandomScale, &gBattleAnimParticleDescriptors[0xF], 0x14, 4, 7, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_CallbackSharedDescriptor13DirectionalSprayScaledFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 4, 7, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_CallbackSharedDirectionalSprayFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 4, 7, 0, 0x25, 0);
}

void BattleAnim_CreateSprayColumnEffect(void) {
    BattleAnim_SpawnDescriptor25AlphaHoldFadeOut(0x2C, 4, 0x10, 0xA, 0xFF);
    BattleAnim_SpawnGlobalTintColorFadeDetach(0x30, 0x20, 0xA);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 5, BattleAnim_CallbackSharedDirectionalSprayFade, &gBattleAnimParticleDescriptors[0x12], 8, 3, 3, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 2, BattleAnim_CallbackSharedDescriptor0FDelayedRisingColumnFade, &gBattleAnimParticleDescriptors[0xF], 0x14, 4, 3, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 2, BattleAnim_CallbackSharedDescriptor0FDelayedRisingColumnRandomScale, &gBattleAnimParticleDescriptors[0xF], 0x14, 4, 3, 0, 0x25, 0);
}

void BattleAnim_CreateSprayColumnEffectTrigger(void) {
    BattleAnim_SpawnDescriptor25AlphaHoldFadeOut(0, 4, 8, 0xA, 0xC8);
    BattleAnim_SpawnGlobalTintColorFadeDetach(0x30, 0x20, 0xA);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 5, BattleAnim_CallbackSharedDirectionalSprayFade, &gBattleAnimParticleDescriptors[0x12], 8, 3, 3, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 2, BattleAnim_CallbackSharedDescriptor0FDelayedRisingColumnFade, &gBattleAnimParticleDescriptors[0xF], 0x14, 4, 3, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 2, BattleAnim_CallbackSharedDescriptor0FDelayedRisingColumnRandomScale, &gBattleAnimParticleDescriptors[0xF], 0x14, 4, 3, 0, 0x25, 0);
    BattleAnim_EndEffect72Descriptor20ModelAnimWaitSequence();
}

void BattleAnim_CreateStreamSprayColumnEffect(void) {
    BattleAnim_SpawnCategory17MarkerSlot(0x64, 1);
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 3);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 3, BattleAnim_CallbackStartEffect59EndEffect28DirectionalStreamFade, &gBattleAnimParticleDescriptors[0x14], 2, 1, 2, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 5, 5, BattleAnim_CallbackStartEffect59EndEffect28DirectionalStreamFade, &gBattleAnimParticleDescriptors[0x13], 2, 1, 2, 0, 0x25, 0);
    BattleAnim_AddSpawnDelay(0x23);
    BattleAnim_SpawnDescriptor25AlphaHoldFadeOutFullAlpha(8, 4, 8, 0xA);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 2, BattleAnim_CallbackSharedDescriptor13DirectionalSprayScaledFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 4, 2, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 5, 2, BattleAnim_CallbackSharedDirectionalSprayFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 4, 2, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 6, 2, BattleAnim_CallbackSharedDescriptor0FDelayedRisingColumnFade, &gBattleAnimParticleDescriptors[0xF], 0x14, 2, 1, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 2, BattleAnim_CallbackSharedDescriptor0FDelayedRisingColumnRandomScale, &gBattleAnimParticleDescriptors[0xF], 0x14, 2, 1, 0, 0x25, 0);
}

void BattleAnim_CreateBurstStreamEffect(void) {
    BattleAnim_SpawnDescriptor25AlphaHoldFadeOutFullAlpha(0x22, 4, 0x10, 0xA);
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x20, 3);
    BattleAnim_SpawnGlobalTintColorFadeDetach(0x30, 0x20, 0xA);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 0xA, 2, BattleAnim_CallbackEndEffect28Descriptor10UpwardBurstFade, &gBattleAnimParticleDescriptors[0x10], 0xC, 1, 3, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 5, 3, BattleAnim_CallbackEndEffect28Descriptor10WideScatterBurstFade, &gBattleAnimParticleDescriptors[0x10], 0xC, 2, 3, 0, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 2, BattleAnim_CallbackStartEffect59EndEffect28DirectionalStreamFade, &gBattleAnimParticleDescriptors[0x13], 0xC, 3, 3, 0, 0x25, 0);
}

void BattleAnim_CreateCollisionRandomEffect(void) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 5, BattleAnim_CallbackStartEffects18And73Descriptor11ScatterRiseFade, &gBattleAnimParticleDescriptors[0x11], 8, 4, 0x10, gParticleTexture_Default, 0x25, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 1, 0x24, BattleAnim_CallbackStartEffect73Descriptor15AnimatedColorImpulseFade, &gBattleAnimParticleDescriptors[0x15], 0, 1, 0x11, gParticleTexture_Default, 0, 0);
}

void BattleAnim_EndEffect70Descriptor0F_13SprayColumnSequence(void) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_CallbackSharedDescriptor13DirectionalSprayScaledFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 4, 7, 0, 0x2C, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(8, 4, 2, BattleAnim_CallbackSharedDirectionalSprayFade, &gBattleAnimParticleDescriptors[0x13], 0x14, 3, 7, 0, 0xF, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackSharedDescriptor0FDelayedRisingColumnFade, &gBattleAnimParticleDescriptors[0xF], 0x14, 1, 7, 0, 0x2C, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackSharedDescriptor0FDelayedRisingColumnRandomScale, &gBattleAnimParticleDescriptors[0xF], 0x14, 1, 7, 0, 0xF, 0);
}
