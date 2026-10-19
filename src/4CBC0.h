#ifndef _4CBC0_H_
#define _4CBC0_H_

#include "global.h"

extern s32 gBattleMusicHandle;
extern u32 D_80079014;

s32 Player_PlaySoundEffect(s32 arg0, s32 arg1, s32 arg2);
void Audio_StopCategory2SoundCommand(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2);
s32 Player_HandleSfx(s32 arg0, s32 arg1, s32 arg2);
void Audio_StopCategory3SoundCommand(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2);
s32 Player_CalcVolume(u32 arg0, u32 arg1);
s32 Player_PlaySpecialSfx(s32 arg0, s32 arg1, s32 arg2);
void Audio_StopCategory4SoundCommand(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2);
s32 PlayAmbientSound(s32 arg0, s32 arg1, s32 arg2);
void Audio_StopCategory5SoundCommand(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2);
s32 Menu_PlaySfx(s32 arg0, s32 arg1, UNUSED s32 arg2);
void Audio_StopCategory6SoundCommand(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2);
s32 PlayBattleCry(s32 arg0, s32 arg1, UNUSED s32 arg2);
void Audio_StopCategory7SoundCommand(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2);
void Audio_SeedRandom(s32 arg0, u32 arg1);
u32 Audio_NextRandom(void);
f32 Audio_RandomFloat(void);
s32 PlayPokemonCry(s32 arg0, s32 arg1, s32 arg2);
void Audio_StopCategory8SoundCommand(s32 arg0, s32 arg1, UNUSED s32 arg2);
s32 PlayBattleMusic(s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2);
void Audio_StopCategory9SoundCommand(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2);
s32 PlayStadiumSfx(s32 arg0, s32 arg1, s32 arg2);
void Audio_StopCategoryASoundCommand(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2);
s32 ResultScreen_PlaySfx(s32 arg0, u32 arg1);
s32 PlaySoundByCategory(s32 arg0, s32 arg1, s32 arg2);
void StopSoundByCategory(s32 arg0, s32 arg1, s32 arg2);
s32 PlayBackgroundMusic(s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2);
s32 PlayUISfx(s32 arg0, s32 arg1, s32 arg2);
s32 PlayResultScreenSfx(s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2);

#endif // _4CBC0_H_
