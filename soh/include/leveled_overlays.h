#ifndef LEVELED_OVERLAYS_H
#define LEVELED_OVERLAYS_H
#include "z64.h"
#endif

void ActorDamageNumber_New(Actor* actor, u16 damage);
void ActorExperienceNumber_New(Actor* actor, u16 experience);
void ActorLevelUp_New(Actor* actor, u8 powerDiff, u8 courageDiff, u16 healthDiff, u8 magicDiff);
void ActorDamageNumber_Draw(PlayState* play, Actor* actor);
void ActorExperienceNumber_Draw(PlayState* play, Actor* actor);
void Actor_LevelUpDraw(PlayState* play, Actor* actor);
void Leveled_ValueNumberDraw(PlayState* play, u16 x, u16 y, u32 value, u8 r, u8 g, u8 b);
void Leveled_BigValueNumberDraw(PlayState* play, u16 x, u16 y, u32 value, u8 r, u8 g, u8 b, u8 a);
void Leveled_KaleidoEquip_Stats(PlayState* play);
void Leveled_Interface_DrawNextLevel(PlayState* play);