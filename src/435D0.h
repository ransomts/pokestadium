#ifndef _435D0_H_
#define _435D0_H_

#include "global.h"
#include "src/373A0.h"

void Audio_ProcessMusic(void);
void Audio_SelectTrack(u8 arg0);
s32 Music_PlayTrack(u16 arg0);
void Audio_ProcessChannel(u32 arg0);
void Audio_ProcessCommand(u32 arg0);
u8 Audio_Command_End(u32 arg0);
u8 Audio_Command_SetAddress(u32 arg0);
u8 Audio_Command_Jump(u32 arg0);
u8 Audio_Command_ToggleLoop(u32 arg0);
u8 Audio_Command_SetEnvelope(u32 arg0);
u8 Audio_Command_SetVibrato(u32 arg0);
u8 Audio_Command_SetTempo(u32 arg0);
u8 Audio_Command_SetBPM(u32 arg0);
u8 Audio_Command_SetMasterVol(u32 arg0);
u8 Audio_Command_ChangeTrack(u32 arg0);
u8 Audio_Command_SetSustain(u32 arg0);
u8 Audio_Command_SetGlobalVol(u32 arg0);
u8 Audio_Command_EnableLoop(u32 arg0);
u8 Audio_Command_SetPitch(u32 arg0, u8 arg1);
u8 Audio_Command_SetInstrument(u32 arg0, u8 arg1);
s32 Audio_Command_PlayNote(u32 arg0, u8 arg1);
u8 Audio_Command_NoteHandler(u32 arg0, u8 arg1);
u8 Audio_Command_NoteUpdate(u32 arg0, u8 arg1);
s32 Audio_CalculateNoteOffset(u32 arg0, u8 arg1);
s32 Audio_UpdateNotePitch(u32 arg0, u16 arg1, u16 arg2);
s32 Audio_UpdateChannelPan(u32 arg0);
s32 Audio_UpdateChannelFreq(u32 arg0);
s32 Audio_WriteNoteData(u32 arg0, u16 arg1);
void Audio_UpdateBPMOffset(void);
void Audio_ApplyPitchBend(u16 arg0, u16 arg1);
s32 Audio_DecrementProgramCounter(u32 arg0);
s32 Audio_IsTrackActive(void);
void Audio_ProcessEnvelope(u32 arg0);
s32 Audio_SetEnvelopeTarget(u32 arg0, u16 arg1);
void Audio_UpdateChannelVolume(u32 arg0);
u8 Audio_FetchCommand(u32 arg0);
u16 Audio_GetApuRegister(u32 arg0, s32 arg1);
u16 Audio_GetFrequencyValue(u8 arg0, u8 arg1);
void Audio_ResetAllChannels(u8 arg0);
void Audio_PrepareTrack(u8 arg0);
void Audio_StopAllTracks(void);
void Audio_LoadTrackData(u8 arg0);
s32 Music_FadeStepComplete(void);
void Music_ResolveTrackOffsets(unk_D_800FC6D4* arg0);

#endif // _435D0_H_
