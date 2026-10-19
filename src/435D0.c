#include "435D0.h"
#include "4A3E0.h"

typedef struct EnvelopeState {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
} EnvelopeState; // size = 0x5

typedef struct VibratoState {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ u8 unk_0C;
} VibratoState; // size = 0x10

static u8 D_800FCD40[8];
static u8 gChannelActiveFlags[8];
static u8 gChannelWaitCounters[8];
static u8 gChannelStatus[8];
static u8 gChannelControl[8];
static u8 gTrackTransitionFlag;
static EnvelopeState gEnvelopeState[8];
static VibratoState gVibratoState[8];
static u8 gChannelSustainValues[8];
static u8 gChannelTempoValues[8];
static u8 gChannelPitchValues[8];
static u8 gChannelJumpCounters[8];
static u8 gChannelInstruments[8];
static u8 gMasterVolume[8];
static u8* gChannelProgramCounters[8];
static s32 gChannelPrevProgramCounters[8];
static s32 gChannelDataBases[8];
static u8 gChannelPitchBase[8];
static u16 gBpmLow;
static u16 gBpmHigh;
static u8 gCurrentTrackId;
static u8 gPitchModifiers[2];
static u8* gCustomWaveforms[2];
static u8 gChannelNoteOffsets[8];
static u32 gCurrentTrackData;
static u8 gTrackPitchOffset;
static u8 gTrackBpmOffset;

static u8 gChannelPanLow[] = {
    0x11, 0x22, 0x44, 0x88, 0x11, 0x22, 0x44, 0x88,
};
static u8 gChannelPanHigh[] = {
    0xEE, 0xDD, 0xBB, 0x77, 0xEE, 0xDD, 0xBB, 0x77,
};
static u8 gTrackRangeStart = 0;
static u8 gTrackRangeEnd = 0xF0;
static u8 gTrackIdLimit = 0xF1;
static u8 gTrackIdMax = 0xFF;
static u8 gTrackMinId = 0;
static u8 gTrackLoadStatus = 0;
static u8 gDefaultWaveform = 0xFF;

void Audio_ProcessMusic(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (gChannelActiveFlags[i] != 0) {
            Audio_ProcessChannel(i);
        }
    }
}

void Audio_SelectTrack(u8 arg0) {
    gCurrentTrackId = arg0;
    if (arg0 == 0xFF) {
        Audio_StopAllTracks();
    } else if ((gTrackIdLimit >= arg0) || (gTrackIdMax < arg0)) {
        Audio_PrepareTrack(arg0);
    } else {
        Audio_ResetAllChannels(arg0);
    }
}

s32 Music_PlayTrack(u16 arg0) {
    s32 a;
    s32 offset;

    if (Music_FadeStepComplete() != 0) {
        return 0;
    }

    Music_ResolveTrackOffsets(D_800FC6D4);

    if (D_800FC6D4->num_entries < arg0) {
        return 0;
    }

    offset = D_800FC6D4->offset;
    Audio_StopAllTracks();

    arg0--;

    a = D_800FC6D4->entries[arg0].unk_00;
    gCurrentTrackId = a;
    gTrackPitchOffset = D_800FC6D4->entries[arg0].unk_02;
    gTrackBpmOffset = D_800FC6D4->entries[arg0].unk_03;
    gCurrentTrackData = offset + a * 0x18;

    Audio_PrepareTrack(a);

    return 1;
}

void Audio_ProcessChannel(u32 arg0) {
    if (gChannelWaitCounters[arg0] < 2) {
        gEnvelopeState[arg0].unk_03 = gEnvelopeState[arg0].unk_04;
        gChannelStatus[arg0] &= (u8)~0x30;
        Audio_ProcessCommand(arg0);
        return;
    }

    gChannelWaitCounters[arg0]--;

    if ((arg0 < 4) && (gChannelActiveFlags[arg0 + 4] != 0)) {
        return;
    }

    if (gChannelStatus[arg0] & 0x40) {
        Audio_UpdateChannelVolume(arg0);
    }

    if ((gChannelControl[arg0] & 1) || (gChannelStatus[arg0] & 4)) {
        if (gChannelStatus[arg0] & 0x10) {
            Audio_ProcessEnvelope(arg0);
        } else if (gEnvelopeState[arg0].unk_03 != 0) {
            gEnvelopeState[arg0].unk_03--;
        } else if (gEnvelopeState[arg0].unk_00 != 0) {
            if (gEnvelopeState[arg0].unk_01 & 0xF) {
                gEnvelopeState[arg0].unk_01--;
            } else {
                u8 sp2F = gEnvelopeState[arg0].unk_01;
                sp2F = (sp2F << 4) | ((sp2F >> 4) & 0xF);

                gEnvelopeState[arg0].unk_01 |= sp2F;

                if ((gChannelStatus[arg0] & 8) != 0) {
                    sp2F = gEnvelopeState[arg0].unk_00 & 0xF;
                    gChannelStatus[arg0] &= ~8;
                    if (gEnvelopeState[arg0].unk_02 < sp2F) {
                        sp2F = gChannelStatus[arg0] * 0;
                    } else {
                        sp2F = gEnvelopeState[arg0].unk_02 - sp2F;
                    }
                } else {
                    sp2F = (gEnvelopeState[arg0].unk_00 & 0xF0) >> 4;
                    gChannelStatus[arg0] &= 8;
                    if ((0xFF - sp2F) < gEnvelopeState[arg0].unk_02) {
                        sp2F = 0xFF;
                    } else {
                        sp2F += gEnvelopeState[arg0].unk_02;
                    }
                }
                GbAudio_QueueRegisterWrite(Audio_GetApuRegister(arg0, 3), sp2F, 0);
            }
        }
    }
}

void Audio_ProcessCommand(u32 arg0) {
    u32 var_v0;
    u8 temp_v0;

    do {
        temp_v0 = Audio_FetchCommand(arg0);
        switch (temp_v0) {
            case 0xFF:
                var_v0 = Audio_Command_End(arg0);
                break;
            case 0xFD:
                var_v0 = Audio_Command_SetAddress(arg0);
                break;
            case 0xFE:
                var_v0 = Audio_Command_Jump(arg0);
                break;
            case 0xE8:
                var_v0 = Audio_Command_ToggleLoop(arg0);
                break;
            case 0xEA:
                var_v0 = Audio_Command_SetEnvelope(arg0);
                break;
            case 0xEB:
                var_v0 = Audio_Command_SetVibrato(arg0);
                break;
            case 0xEC:
                var_v0 = Audio_Command_SetTempo(arg0);
                break;
            case 0xED:
                var_v0 = Audio_Command_SetBPM(arg0);
                break;
            case 0xEE:
                var_v0 = Audio_Command_SetMasterVol(arg0);
                break;
            case 0xEF:
                var_v0 = Audio_Command_ChangeTrack(arg0);
                break;
            case 0xFC:
                var_v0 = Audio_Command_SetSustain(arg0);
                break;
            case 0xF0:
                var_v0 = Audio_Command_SetGlobalVol(arg0);
                break;
            case 0xF8:
                var_v0 = Audio_Command_EnableLoop(arg0);
                break;
            default:
                switch (temp_v0 & 0xF0) {
                    case 0xD0:
                        var_v0 = Audio_Command_SetPitch(arg0, temp_v0);
                        break;
                    case 0xE0:
                        var_v0 = Audio_Command_SetInstrument(arg0, temp_v0);
                        break;
                    case 0x20:
                        var_v0 = Audio_Command_PlayNote(arg0, temp_v0);
                        break;
                    default:
                        var_v0 = Audio_Command_NoteHandler(arg0, temp_v0);
                        break;
                }
                break;
        }
    } while (!var_v0 ^ 0);
}

u8 Audio_Command_End(u32 arg0) {
    if (gChannelStatus[arg0] & 2) {
        gChannelStatus[arg0] &= ~2;
        gChannelPrevProgramCounters[arg0] = gChannelProgramCounters[arg0];
        return 0;
    }

    if (arg0 >= 3) {
        gChannelStatus[arg0] &= ~4;
        gChannelControl[arg0] &= ~1;
        if (arg0 == 6) {
            GbAudio_QueueRegisterWrite(0xFF1A, 0, 0);
            GbAudio_QueueRegisterWrite(0xFF1A, 0x80, 0);
        }

        if (gTrackTransitionFlag != 0) {
            gTrackTransitionFlag = 0;
        }
        GbAudio_QueueRegisterWrite(0xFF25, gChannelPanHigh[arg0] & GbAudio_GetRegisterValue(0xFF25), 0);
    }

    gChannelActiveFlags[arg0] = 0;

    if ((gChannelActiveFlags[4] >= gTrackRangeStart) && (gChannelActiveFlags[4] < gTrackRangeEnd)) {
        if ((arg0 != 4) && (Audio_DecrementProgramCounter(arg0) != 0)) {
            return 1;
        } else {
            GbAudio_QueueRegisterWrite(0xFF24, gMasterVolume[0], 0);
            gMasterVolume[0] = 0;
            gChannelActiveFlags[arg0] = 0;
        }
    }
    return 1;
}

u8 Audio_Command_SetAddress(u32 arg0) {
    u8 sp1F;
    u8 temp_v0;
    s32 tmp;

    sp1F = Audio_FetchCommand(arg0);
    temp_v0 = Audio_FetchCommand(arg0);
    tmp = (temp_v0 << 8) + sp1F;

    gChannelPrevProgramCounters[arg0] = gChannelProgramCounters[arg0];
    gChannelProgramCounters[arg0] = tmp + gChannelDataBases[arg0];
    gChannelStatus[arg0] |= 2;
    return 0;
}

u8 Audio_Command_Jump(u32 arg0) {
    u8 sp27;
    u8 sp26;
    u32 temp_v0 = Audio_FetchCommand(arg0);

    if (temp_v0) {
        if (gChannelJumpCounters[arg0] == temp_v0) {
            gChannelJumpCounters[arg0] = 1;
            Audio_FetchCommand(arg0);
            Audio_FetchCommand(arg0);
            return 0;
        }
        gChannelJumpCounters[arg0]++;
    }

    sp27 = Audio_FetchCommand(arg0);
    sp26 = Audio_FetchCommand(arg0);

    gChannelProgramCounters[arg0] = (u8*)gChannelDataBases + ((sp26 << 8) | sp27);
    return 0;
}

u8 Audio_Command_ToggleLoop(u32 arg0) {
    gChannelStatus[arg0] ^= 1;
    return 0;
}

u8 Audio_Command_SetEnvelope(u32 arg0) {
    u8 temp_a0;
    u8 temp_a1;
    u8 temp_v0;
    u8 temp_t9;

    temp_v0 = Audio_FetchCommand(arg0);
    gEnvelopeState[arg0].unk_03 = temp_v0;
    gEnvelopeState[arg0].unk_04 = temp_v0;

    temp_v0 = Audio_FetchCommand(arg0);
    temp_a0 = temp_v0 & 0xF0;
    temp_a0 >>= 4;
    temp_a1 = temp_a0;
    temp_a1 >>= 1;
    temp_t9 = temp_a0 & 1;
    temp_a0 = temp_a1 + temp_t9;
    temp_a0 <<= 4;
    temp_t9 = temp_a0 | temp_a1;
    gEnvelopeState[arg0].unk_00 = temp_t9;

    temp_t9 = temp_v0 & 0xF;
    temp_v0 = temp_t9 << 4;
    temp_v0 |= temp_t9;
    gEnvelopeState[arg0].unk_01 = temp_v0;
    return 0;
}

u8 Audio_Command_SetVibrato(u32 arg0) {
    UNUSED s32 pad;
    u8 temp_v0;

    gVibratoState[arg0].unk_0C = Audio_FetchCommand(arg0);
    temp_v0 = Audio_FetchCommand(arg0);
    gVibratoState[arg0].unk_04 = Audio_GetFrequencyValue(temp_v0 & 0xF, (temp_v0 & 0xF0) >> 4);
    gChannelStatus[arg0] |= 0x10;
    Audio_CalculateNoteOffset(arg0, Audio_FetchCommand(arg0));
    return 1;
}

u8 Audio_Command_SetTempo(u32 arg0) {
    gChannelTempoValues[arg0] = Audio_FetchCommand(arg0) << 6;
    return 0;
}

u8 Audio_Command_SetBPM(u32 arg0) {
    u8 sp1F;
    u8 sp1E;

    if (arg0 < 4) {
        sp1F = Audio_FetchCommand(arg0);
        sp1E = Audio_FetchCommand(arg0);
        gBpmLow = (sp1E << 8) + sp1F;
        gChannelNoteOffsets[0] = 0;
        gChannelNoteOffsets[1] = 0;
        gChannelNoteOffsets[2] = 0;
        gChannelNoteOffsets[3] = 0;
    } else {
        sp1F = Audio_FetchCommand(arg0);
        sp1E = Audio_FetchCommand(arg0);
        gBpmHigh = (sp1E << 8) + sp1F;
        gChannelNoteOffsets[4] = 0;
        gChannelNoteOffsets[5] = 0;
        gChannelNoteOffsets[6] = 0;
        gChannelNoteOffsets[7] = 0;
    }
    return 0;
}

u8 Audio_Command_SetMasterVol(u32 arg0) {
    gMasterVolume[1] = Audio_FetchCommand(arg0);
    return 0;
}

u8 Audio_Command_ChangeTrack(u32 arg0) {
    Audio_SelectTrack(Audio_FetchCommand(arg0));
    if (gTrackTransitionFlag == 0) {
        gTrackTransitionFlag = gChannelActiveFlags[7];
        gChannelActiveFlags[7] = 0;
    }
    return 0;
}

u8 Audio_Command_SetSustain(u32 arg0) {
    u8 temp_v0 = Audio_FetchCommand(arg0);

    gChannelSustainValues[arg0] = temp_v0;
    gChannelTempoValues[arg0] = temp_v0 & 0xC0;
    gChannelStatus[arg0] |= 0x40;
    return 0;
}

u8 Audio_Command_SetGlobalVol(u32 arg0) {
    GbAudio_QueueRegisterWrite(0xFF24, Audio_FetchCommand(arg0), 0);
    return 0;
}

u8 Audio_Command_EnableLoop(u32 arg0) {
    gChannelControl[arg0] |= 1;
    return 0;
}

u8 Audio_Command_SetPitch(u32 arg0, u8 arg1) {
    u8 var_a1;

    gChannelPitchBase[arg0] = arg1 & 0xF;
    if (arg0 != 3) {
        var_a1 = Audio_FetchCommand(arg0);
        if (arg0 == 2) {
            gPitchModifiers[0] = var_a1 & 0xF;
            var_a1 = (var_a1 & 0x30) * 2;
        } else if (arg0 == 6) {
            gPitchModifiers[1] = var_a1 & 0xF;
            var_a1 = (var_a1 & 0x30) * 2;
        }
        gChannelPitchValues[arg0] = var_a1;
    }
    return 0;
}

u8 Audio_Command_SetInstrument(u32 arg0, u8 arg1) {
    gChannelInstruments[arg0] = arg1 & 0xF;
    return 0;
}

s32 Audio_Command_PlayNote(u32 arg0, u8 arg1) {
    u8 sp27;
    u8 sp26;
    u8 sp25;
    u32 var_v1;

    if (((arg1 & 0xF0) != 0x20) || (arg0 < 3) || (gChannelControl[arg0] & 1)) {
        var_v1 = Audio_Command_NoteHandler(arg0, arg1);
    } else {
        sp25 = gChannelTempoValues[arg0] | Audio_CalculateNoteOffset(arg0, arg1);
        GbAudio_QueueRegisterWrite(Audio_GetApuRegister(arg0, 1), sp25, 0);
        sp27 = Audio_FetchCommand(arg0);
        GbAudio_QueueRegisterWrite(Audio_GetApuRegister(arg0, 2), sp27, 0);
        sp26 = Audio_FetchCommand(arg0);
        sp27 = 0;
        if (arg0 != 7) {
            sp27 = Audio_FetchCommand(arg0);
        }
        Audio_UpdateChannelFreq(arg0);
        Audio_UpdateChannelPan(arg0);
        Audio_WriteNoteData(arg0, (sp27 << 8) + sp26);
        var_v1 = 1;
    }
    return var_v1;
}

u8 Audio_Command_NoteHandler(u32 arg0, u8 arg1) {
    if (arg0 < 4) {
        Audio_Command_NoteUpdate(arg0, arg1);
    }

    if (arg1 != 0x10) {
        Audio_Command_NoteUpdate(arg0, arg1);
        return 1;
    }

    if (gChannelControl[arg0] & 1) {
        Audio_Command_NoteUpdate(arg0, arg1);
        return 1;
    }

    GbAudio_QueueRegisterWrite(0xFF10, Audio_FetchCommand(arg0), 0);
    return 0;
}

u8 Audio_Command_NoteUpdate(u32 arg0, u8 arg1) {
    u8 sp1F;
    s32 temp_v0 = arg1 & 0xF0;

    if ((arg0 != 3) || (temp_v0 > 0xB0)) {
        Audio_CalculateNoteOffset(arg0, arg1);
    } else {
        if (temp_v0 == 0xB0) {
            sp1F = Audio_FetchCommand(arg0);
        } else {
            sp1F = temp_v0 >> 4;
        }

        if (gTrackTransitionFlag == 0) {
            Audio_SelectTrack(gCurrentTrackId);
        }
    }

    Audio_CalculateNoteOffset(arg0, sp1F);
    return 1;
}

s32 Audio_CalculateNoteOffset(u32 arg0, u8 arg1) {
    u16 sp26;
    u16 tmp;
    u16 var_t0;
    u16 sp20;
    u8 sp1F;

    sp26 = (gChannelPitchBase[arg0] * ((arg1 & 0xF) + 1));
    var_t0 = 0x100;
    if (arg0 >= 4) {
        if (arg0 != 7) {
            Audio_UpdateBPMOffset();
            var_t0 = gBpmHigh;
        }
    } else {
        var_t0 = gBpmLow;
    }

    tmp = (gChannelNoteOffsets[arg0] + (sp26 * var_t0));
    gChannelNoteOffsets[arg0] = tmp & 0xFFFF;
    gChannelWaitCounters[arg0] = (tmp & 0xFF00) >> 8;

    if (!(gChannelControl[arg0] & 1) && (gChannelStatus[arg0] & 4)) {
        return gChannelWaitCounters[arg0];
    } else if ((arg1 & 0xF0) != 0xC0) {
        return Audio_UpdateNotePitch(arg0, arg1, tmp);
    } else if ((arg0 < 4) && (gChannelActiveFlags[4 + arg0] != 0)) {
        return gChannelActiveFlags[4 + arg0];
    } else if ((arg0 == 2) || (arg0 == 6)) {
        sp1F = gChannelPanHigh[arg0] | GbAudio_GetRegisterValue(0xFF25);
        GbAudio_QueueRegisterWrite(0xFF25, sp1F, 0);
        return sp1F;
    } else {
        sp20 = Audio_GetApuRegister(arg0, 2);
        GbAudio_QueueRegisterWrite(sp20, 8, 0);
        GbAudio_QueueRegisterWrite(sp20 + 2, 0x80, 0);
    }

    return 0x80;
}

s32 Audio_UpdateNotePitch(u32 arg0, u16 arg1, u16 arg2) {
    u16 var_s1;
    s32 tmp;
    u8 tmp1;

    arg1 = (arg1 & 0xF0) >> 8;

    tmp1 = gChannelInstruments[arg0];
    var_s1 = Audio_GetFrequencyValue(arg1, tmp1);
    tmp = gChannelStatus[arg0] == 0;

    if (tmp & 0x10) {
        Audio_SetEnvelopeTarget(arg0, var_s1);
    }

    if ((arg0 < 4) && (gChannelActiveFlags[4 + arg0] != 0)) {
        return 1;
    }

    GbAudio_QueueRegisterWrite(Audio_GetApuRegister(arg0, 2), gChannelPitchValues[arg0], 0);
    Audio_UpdateChannelFreq(arg0);
    Audio_UpdateChannelPan(arg0);
    if (gChannelStatus[arg0] & 1) {
        var_s1++;
    }
    gEnvelopeState[arg0].unk_02 = var_s1 & 0xFF;
    Audio_WriteNoteData(arg0, var_s1);
    return 1;
}

s32 Audio_UpdateChannelPan(u32 arg0) {
    u8 tmp;
    u8 sp1E;
    u8 temp_v1 = gChannelPanLow[arg0] | GbAudio_GetRegisterValue(0xFF25);

    if ((arg0 >= 4) && (arg0 != 7)) {
        GbAudio_QueueRegisterWrite(0xFF25, temp_v1, 0);
        return 1;
    }

    if ((arg0 != 7) && (gChannelActiveFlags[4 + arg0] != 0)) {
        GbAudio_QueueRegisterWrite(0xFF25, temp_v1, 0);
        return 1;
    }

    sp1E = (gMasterVolume[1] & gChannelPanLow[arg0]);
    tmp = gChannelPanHigh[arg0] & GbAudio_GetRegisterValue(0xFF25);
    tmp |= sp1E;
    GbAudio_QueueRegisterWrite(0xFF25, tmp, 0);
    return 1;
}

s32 Audio_UpdateChannelFreq(u32 arg0) {
    u8 sp1F = gChannelWaitCounters[arg0];
    u8 tmp;

    if ((arg0 != 2) && (arg0 != 6)) {
        tmp = gChannelTempoValues[arg0];

        sp1F &= 0x3F;
        sp1F |= tmp;
    }
    GbAudio_QueueRegisterWrite(Audio_GetApuRegister(arg0, 1), sp1F, 0);
    return 1;
}

s32 Audio_WriteNoteData(u32 arg0, u16 arg1) {
    u8 sp2E[4];
    s32 var_s2;
    u16 temp_v0;

    if ((arg0 == 2) || (arg0 == 6)) {
        s32 i;

        if (arg0 == 2) {
            var_s2 = 0;
        } else {
            var_s2 = 1;
        }
        GbAudio_QueueRegisterWrite(0xFF1A, 0, 0);

        for (i = 0; i < 16; i++) {
            GbAudio_QueueRegisterWrite(i + 0x20, gCustomWaveforms[var_s2][i], 0);
        }

        GbAudio_QueueRegisterWrite(0xFF1A, 0x80, 0);
    }

    {
        u32 new_var2 = arg1 & 0xFF;
        u32 new_var = (((arg1 >> 8) & 0xFF) | 0x80) & 0xC7;

        sp2E[2] = new_var2;
        sp2E[3] = new_var;

        temp_v0 = Audio_GetApuRegister(arg0, 3);
        GbAudio_QueueRegisterWrite(temp_v0, new_var2, 0);
        GbAudio_QueueRegisterWrite(temp_v0 + 1, new_var, 0);

        if (gChannelActiveFlags[4] != 0) {
            Audio_ApplyPitchBend(sp2E[2] + (sp2E[3] << 8), temp_v0);
        }
    }
    return 1;
}

void Audio_UpdateBPMOffset(void) {
    s32 tmp;

    if (Audio_IsTrackActive() != 0) {
        tmp = gTrackBpmOffset + 0x80;
        gBpmHigh = tmp;
    } else {
        gBpmHigh = 0x100;
    }
}

void Audio_ApplyPitchBend(u16 arg0, u16 arg1) {
    if (Audio_IsTrackActive() != 0) {
        u16 sp18 = gTrackPitchOffset;

        arg0 += sp18;
        GbAudio_QueueRegisterWrite(arg1, arg0 & 0xFF, 0);
        GbAudio_QueueRegisterWrite(arg1 + 1, (arg0 >> 8) & 0xFF, 0);
    }
}

s32 Audio_DecrementProgramCounter(u32 arg0) {
    if (Audio_IsTrackActive() != 0) {
        gChannelProgramCounters[arg0]--;
        return 1;
    }
    return 0;
}

s32 Audio_IsTrackActive(void) {
    if ((gChannelActiveFlags[4] < gTrackRangeEnd) && (gChannelActiveFlags[4] >= gTrackRangeStart)) {
        return 1;
    }
    return 0;
}

void Audio_ProcessEnvelope(u32 arg0) {
    u8 sp1F;
    u8 sp1E;
    u16 sp1C;

    gVibratoState[arg0].unk_00 += gVibratoState[arg0].unk_08;
    if (gChannelStatus[arg0] & 0x20) {
        if (gVibratoState[arg0].unk_04 < gVibratoState[arg0].unk_00) {
            gChannelStatus[arg0] &= ~0x30;
            return;
        }
    } else if (gVibratoState[arg0].unk_00 < gVibratoState[arg0].unk_04) {
        gChannelStatus[arg0] &= ~0x30;
        return;
    }

    sp1F = gVibratoState[arg0].unk_00;
    sp1E = ((u16)gVibratoState[arg0].unk_00 & 0xFF00) >> 8;
    sp1C = Audio_GetApuRegister(arg0, 3);
    GbAudio_QueueRegisterWrite(sp1C, sp1F, 0);
    GbAudio_QueueRegisterWrite(sp1C + 1, sp1E, 0);
}

s32 Audio_SetEnvelopeTarget(u32 arg0, u16 arg1) {
    gVibratoState[arg0].unk_00 = arg1;
    if (arg1 < gVibratoState[arg0].unk_04) {
        gChannelStatus[arg0] &= ~0x20;
    } else {
        gChannelStatus[arg0] |= 0x20;
    }
    gVibratoState[arg0].unk_08 = (gVibratoState[arg0].unk_04 - gVibratoState[arg0].unk_00) / gVibratoState[arg0].unk_0C;
    return 1;
}

void Audio_UpdateChannelVolume(u32 arg0) {
    u8 sp1F;
    u16 sp1C;

    sp1F = gChannelSustainValues[arg0];
    sp1F &= 0xC0;
    gChannelSustainValues[arg0] *= 4;
    gChannelSustainValues[arg0] |= (sp1F >> 6);
    sp1F &= 0xC0;
    sp1C = Audio_GetApuRegister(arg0, 1);
    GbAudio_QueueRegisterWrite(sp1C, (sp1F | (GbAudio_GetRegisterValue(sp1C) & 0x3F) & 0xFF), 0);
}

u8 Audio_FetchCommand(u32 arg0) {
    return *gChannelProgramCounters[arg0]++;
}

u16 Audio_GetApuRegister(u32 arg0, s32 arg1) {
    UNUSED s32 pad;
    u16 D_800785BC[] = {
        0xFF10, 0XFF15, 0xFF1A, 0XFF1F, 0xFF10, 0XFF15, 0xFF1A, 0XFF1F,
    };
    s32 ret = D_800785BC[arg0] + arg1;

    return ret;
}

u16 Audio_GetFrequencyValue(u8 arg0, u8 arg1) {
    s16 sp8[] = {
        0xF82C, 0xF89D, 0xF907, 0xF96B, 0xF9CA, 0xFA23, 0xFA77, 0xFAC7, 0xFB12, 0xFB58, 0xFB9B, 0xFBDA,
    };
    s16 ret = sp8[arg0];

    ret >>= 7 - arg1;
    ret += 0x800;
    return ret;
}

void Audio_ResetAllChannels(u8 arg0) {
    s32 i;

    gTrackTransitionFlag = 0;
    gBpmLow = 0x100;
    gPitchModifiers[0] = 0;
    gPitchModifiers[1] = 0;

    for (i = 0; i < 8; i++) {
        gChannelPrevProgramCounters[i] = 0;
        gChannelProgramCounters[i] = 0;
    }

    for (i = 0; i < 4; i++) {
        gChannelActiveFlags[i] = 0;
        gChannelStatus[i] = 0;
        gChannelTempoValues[i] = 0;
        gChannelSustainValues[i] = 0;

        gEnvelopeState[i].unk_03 = 0;
        gEnvelopeState[i].unk_00 = 0;
        gEnvelopeState[i].unk_01 = 0;
        gEnvelopeState[i].unk_02 = 0;
        gEnvelopeState[i].unk_04 = 0;

        gChannelControl[i] = 0;

        gVibratoState[i].unk_0C = 0;
        gVibratoState[i].unk_00 = 0;
        gVibratoState[i].unk_04 = 0;
        gVibratoState[i].unk_08 = 0;

        gChannelJumpCounters[i] = 1;
        gChannelWaitCounters[i] = 1;
        gChannelPitchBase[i] = 1;
    }

    gMasterVolume[1] = 0xFF;
    GbAudio_QueueRegisterWrite(0xFF24, 0, 0);
    GbAudio_QueueRegisterWrite(0xFF10, 8, 0);
    GbAudio_QueueRegisterWrite(0xFF25, 0, 0);
    GbAudio_QueueRegisterWrite(0xFF1A, 0, 0);
    GbAudio_QueueRegisterWrite(0xFF1A, 0x80, 0);
    GbAudio_QueueRegisterWrite(0xFF24, 0x77, 0);
    Audio_LoadTrackData(arg0);
}

void Audio_PrepareTrack(u8 arg0) {
    u8 i;

    gMasterVolume[1] = 0xFF;

    for (i = 4; i < 7; i++) {
        if (i == 6) {
            continue;
        }

        if (gChannelActiveFlags[i]) {
            if (i == 7) {
                if (arg0 < gTrackMinId) {
                    return;
                }
                if ((gChannelActiveFlags[i] < gTrackMinId) && (gChannelActiveFlags[i] < arg0)) {
                    return;
                }
            } else if (gChannelActiveFlags[i] < arg0) {
                return;
            }
        }

        gChannelPrevProgramCounters[i] = 0;
        gChannelProgramCounters[i] = 0;
        gChannelActiveFlags[i] = 0;

        gChannelStatus[i] = 0;
        gChannelTempoValues[i] = 0;
        gChannelSustainValues[i] = 0;

        gEnvelopeState[i].unk_03 = 0;
        gEnvelopeState[i].unk_00 = 0;
        gEnvelopeState[i].unk_01 = 0;
        gEnvelopeState[i].unk_02 = 0;
        gEnvelopeState[i].unk_04 = 0;

        gVibratoState[i].unk_0C = 0;
        gVibratoState[i].unk_00 = 0.0f;
        gVibratoState[i].unk_04 = 0.0f;
        gVibratoState[i].unk_08 = 0.0f;

        gChannelJumpCounters[i] = 1;
        gChannelWaitCounters[i] = 1;
        gChannelPitchBase[i] = 1;

        if (i == 4) {
            GbAudio_QueueRegisterWrite(0xFF10, 8, 0);
        }
    }

    Audio_LoadTrackData(arg0);
}

void Audio_StopAllTracks(void) {
    s32 i;

    GbAudio_QueueRegisterWrite(0xFF26, 0x80, 0);
    GbAudio_QueueRegisterWrite(0xFF1A, 0x80, 0);
    GbAudio_QueueRegisterWrite(0xFF25, 0, 0);
    GbAudio_QueueRegisterWrite(0xFF1C, 0, 0);
    GbAudio_QueueRegisterWrite(0xFF10, 8, 0);
    GbAudio_QueueRegisterWrite(0xFF12, 8, 0);
    GbAudio_QueueRegisterWrite(0xFF17, 8, 0);
    GbAudio_QueueRegisterWrite(0xFF21, 8, 0);
    GbAudio_QueueRegisterWrite(0xFF14, 0x40, 0);
    GbAudio_QueueRegisterWrite(0xFF19, 0x40, 0);
    GbAudio_QueueRegisterWrite(0xFF23, 0x40, 0);
    GbAudio_QueueRegisterWrite(0xFF24, 0x77, 0);

    gTrackTransitionFlag = 0;
    gTrackLoadStatus = 0;
    gBpmLow = 0x100;
    gBpmHigh = 0x100;
    gPitchModifiers[0] = 0;
    gPitchModifiers[1] = 0;

    for (i = 0; i < 8; i++) {
        gChannelWaitCounters[i] = 1;
        gChannelJumpCounters[i] = 1;
        gChannelPitchBase[i] = 1;
    }

    gMasterVolume[1] = 0xFF;
}

void Audio_LoadTrackData(u8 arg0) {
    u32 i;
    u8 x;
    u8 temp;
    u8 temp_v1;

    temp_v1 = ((unk_D_800FC6D4_008*)gCurrentTrackData)->unk_04;
    temp = (temp_v1 >> 6) & 3;
    x = temp_v1 & 0xF;
    i = 0;
    while (1) {
        gChannelActiveFlags[x] = arg0 + 1;
        if (x >= 3) {
            gChannelStatus[x] |= 4;
        }

        gChannelProgramCounters[x] = ((unk_D_800FC6D4_008*)gCurrentTrackData + i)->unk_00;
        gChannelDataBases[x] = gChannelProgramCounters[x];
        i++;
        
        if (i > temp) {
            break;
        }
        x = ((unk_D_800FC6D4_008*)gCurrentTrackData + i)->unk_04 & 0xF;
    }

    if ((arg0 >= gTrackRangeStart) && (arg0 < gTrackRangeEnd)) {
        gChannelActiveFlags[4] = arg0 + 1;
        gChannelActiveFlags[5] = arg0 + 1;
        gChannelActiveFlags[6] = arg0 + 1;
        gChannelActiveFlags[7] = arg0 + 1;
        gChannelProgramCounters[6] = &gDefaultWaveform;
        if (gMasterVolume[0] == 0) {
            gMasterVolume[0] = GbAudio_GetRegisterValue(0xFF24);
            GbAudio_QueueRegisterWrite(0xFF24, 0x77, 0);
        }
    }
}

s32 Music_FadeStepComplete(void) {
    s32 ret = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (gChannelActiveFlags[4 + i] != 0) {
            ret++;
        }
    }

    return ret;
}

typedef struct unk_80044A50_008 {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u32 unk_04;
} unk_80044A50_008; // size = 0x8

void Music_ResolveTrackOffsets(unk_D_800FC6D4* arg0) {
    s32 i;
    s32 end;
    u32 base;
    u8* temp_v1;
    unk_80044A50_008* temp_v0;

    if (arg0->flags != 0) {
        return;
    }

    end = arg0->unk_04;
    base = (u32)arg0;
    temp_v1 = arg0->offset;
    temp_v1 += base;
    arg0->offset = (u32)temp_v1;

    for (i = 0; i != (end * 3); i++) {
        temp_v0 = (unk_80044A50_008*)((u32)i * 8 + (u32)temp_v1);
        // IDO needs the separate += 0 to match the og register allocation
        temp_v0 += 0;
        temp_v0->unk_00 += base;
    }

    arg0->flags = 1;
}
