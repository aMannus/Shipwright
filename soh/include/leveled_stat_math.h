#ifndef LEVELED_STAT_MATH_H
#define LEVELED_STAT_MATH_H
#define HEALTH_ATTACK_MULTIPLIER 5
#include "z64.h"
#endif

u16 GetActorStat_DisplayAttack(u8 attack, u8 power);
u16 GetActorStat_Attack(u8 attack, u8 power);
u8 GetActorStat_Power(u8 level);
u8 GetActorStat_Courage(u8 level);
u8 GetActorStat_PlayerPower(u8 level);
u8 GetActorStat_PlayerCourage(u8 level);
u16 GetActorStat_EnemyMaxHealth(u16 baseHealth, u8 level);
u8 GetPlayerStat_BonusHearts(u8 level);
u8 GetPlayerStat_MagicUnits(u8 level);
u16 GetPlayerStat_GetModifiedHealthCapacity(u16 baseHealth, u8 level);
u16 GetPlayerStat_NextLevelExpAtLevel(u8 level);
u16 GetActorStat_NextLevelExp(u8 level, u32 currentExp);
f32 Leveled_DamageFormula(f32 attack, u8 power, u8 courage);
f32 Leveled_DamageModify(Actor* actor, Actor* attackingActor, f32 attack);
u16 Leveled_GoldSkulltulaExperience(u8 tokens);
void Leveled_SetPlayerModifiedStats(Player* player);