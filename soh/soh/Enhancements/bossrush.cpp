#include "bossrush.h"

#include "global.h"
#include <Cvar.h>

extern "C" void BossRush_SpawnBlueWarps(PlayState* play) {

    // Spawn blue warps in Chamber of Sages based on what bosses have been defeated.
    if (gSaveContext.linkAge == LINK_AGE_CHILD) {
        // Forest Medallion (Gohma)
        if (!Flags_GetRandomizerInf(RAND_INF_DUNGEONS_DONE_DEKU_TREE)) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_DOOR_WARP1, -100, 6, -170, 0, 0, 0, WARP_DUNGEON_ADULT, false);
        }
        // Fire Medallion (King Dodongo)
        if (!Flags_GetRandomizerInf(RAND_INF_DUNGEONS_DONE_DODONGOS_CAVERN)) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_DOOR_WARP1, 100, 6, -170, 0, 0, 0, WARP_DUNGEON_ADULT, false);
        }
        // Water Medallion (Barinade)
        if (!Flags_GetRandomizerInf(RAND_INF_DUNGEONS_DONE_JABU_JABUS_BELLY)) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_DOOR_WARP1, 199, 6, 0, 0, 0, 0, WARP_DUNGEON_ADULT, false);
        }
    } else {
        // Light Medallion (Ganondorf)
        if (CheckDungeonCount() == 8) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_DOOR_WARP1, -199, 6, 0, 0, 0, 0, WARP_DUNGEON_ADULT, false);
        }
        // Forest Medallion (Phantom Ganondorf)
        if (!Flags_GetRandomizerInf(RAND_INF_DUNGEONS_DONE_FOREST_TEMPLE)) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_DOOR_WARP1, -100, 6, -170, 0, 0, 0, WARP_DUNGEON_ADULT, false);
        }
        // Fire Medallion (Volvagia)
        if (!Flags_GetRandomizerInf(RAND_INF_DUNGEONS_DONE_FIRE_TEMPLE)) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_DOOR_WARP1, 100, 6, -170, 0, 0, 0, WARP_DUNGEON_ADULT, false);
        }
        // Water Medallion (Morpha)
        if (!Flags_GetRandomizerInf(RAND_INF_DUNGEONS_DONE_WATER_TEMPLE)) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_DOOR_WARP1, 199, 6, 0, 0, 0, 0, WARP_DUNGEON_ADULT, false);
        }
        // Spirit Medallion (Twinrova)
        if (!Flags_GetRandomizerInf(RAND_INF_DUNGEONS_DONE_SPIRIT_TEMPLE)) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_DOOR_WARP1, 100, 6, 170, 0, 0, 0, WARP_DUNGEON_ADULT, false);
        }
        // Shadow Medallion (Bongo Bongo)
        if (!Flags_GetRandomizerInf(RAND_INF_DUNGEONS_DONE_SHADOW_TEMPLE)) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_DOOR_WARP1, -100, 6, 170, 0, 0, 0, WARP_DUNGEON_ADULT, false);
        }
    }
}

extern "C" void BossRush_HandleBlueWarp(DoorWarp1* warp, PlayState* play) {

    // If warping from Chamber of Sages, choose the correct boss room to teleport to.
    if (play->sceneNum == SCENE_KENJYANOMA) {
        f32 warpPosX = warp->actor.world.pos.x;
        f32 warpPosZ = warp->actor.world.pos.z;
        // Gohma & Phantom Ganon
        if (warpPosX == -100 && warpPosZ == -170) {
            if (gSaveContext.linkAge == LINK_AGE_CHILD) {
                play->nextEntranceIndex = 0x040F;
            } else {
                play->nextEntranceIndex = 0x000C;
            }
        // King Dodongo & Volvagia
        } else if (warpPosX == 100 && warpPosZ == -170) {
            if (gSaveContext.linkAge == LINK_AGE_CHILD) {
                play->nextEntranceIndex = 0x040B;
            } else {
                play->nextEntranceIndex = 0x0305;
            }
        // Barinade & Morb
        } else if (warpPosX == 199 && warpPosZ == 0) {
            if (gSaveContext.linkAge == LINK_AGE_CHILD) {
                play->nextEntranceIndex = 0x0301;
            } else {
                play->nextEntranceIndex = 0x0417;
            }
        // Twinrova
        } else if (warpPosX == 100 && warpPosZ == 170) {
            play->nextEntranceIndex = 0x05EC;
        // Bongo Bongo
        } else if (warpPosX == -100 && warpPosZ == 170) {
            play->nextEntranceIndex = 0x0413;
        // Ganondork
        } else if (warpPosX == -199 && warpPosZ == 0) {
            play->nextEntranceIndex = 0x041F;
        }
    // If coming from a boss room, teleport back to Chamber of Sages and set flag.
    } else {
        play->nextEntranceIndex = SCENE_HAIRAL_NIWA2;
        switch (play->sceneNum) {
            case SCENE_YDAN_BOSS:
                Flags_SetRandomizerInf(RAND_INF_DUNGEONS_DONE_DEKU_TREE);
                break;
            case SCENE_DDAN_BOSS:
                Flags_SetRandomizerInf(RAND_INF_DUNGEONS_DONE_DODONGOS_CAVERN);
                break;
            case SCENE_BDAN_BOSS:
                Flags_SetRandomizerInf(RAND_INF_DUNGEONS_DONE_JABU_JABUS_BELLY);
                break;
            case SCENE_MORIBOSSROOM:
                Flags_SetRandomizerInf(RAND_INF_DUNGEONS_DONE_FOREST_TEMPLE);
                break;
            case SCENE_FIRE_BS:
                Flags_SetRandomizerInf(RAND_INF_DUNGEONS_DONE_FIRE_TEMPLE);
                break;
            case SCENE_MIZUSIN_BS:
                Flags_SetRandomizerInf(RAND_INF_DUNGEONS_DONE_WATER_TEMPLE);
                break;
            case SCENE_JYASINBOSS:
                Flags_SetRandomizerInf(RAND_INF_DUNGEONS_DONE_SPIRIT_TEMPLE);
                break;
            case SCENE_HAKADAN_BS:
                Flags_SetRandomizerInf(RAND_INF_DUNGEONS_DONE_SHADOW_TEMPLE);
                break;
            default:
                break;
        }

        // When 3 bosses (all child bosses) are defeated, change to Adult Link.
        if (CheckDungeonCount() == 3) {
            play->linkAgeOnLoad = LINK_AGE_ADULT;
            gSaveContext.linkAge = LINK_AGE_ADULT;
            BossRush_SetEquipment(LINK_AGE_ADULT);
        }
    }
}

void BossRush_InitSave() {

    // Set player name to Link just in case it'll be used in textboxes. Player can't input their own name.
    static std::array<char, 8> sPlayerName = { 0x15, 0x12, 0x17, 0x14, 0x3E, 0x3E, 0x3E, 0x3E };
    for (int i = 0; i < ARRAY_COUNT(gSaveContext.playerName); i++) {
        gSaveContext.playerName[i] = sPlayerName[i];
    }

    gSaveContext.linkAge = LINK_AGE_CHILD;
    gSaveContext.entranceIndex = 107;
    gSaveContext.cutsceneIndex = 0x8000;
    gSaveContext.healthCapacity = 160;
    gSaveContext.health = 160;
    gSaveContext.magicLevel = 0;
    gSaveContext.magic = 0x30;
    gSaveContext.isMagicAcquired = 1;

    // Skip boss cutscenes
    gSaveContext.eventChkInf[7] |= 1;    // gohma
    gSaveContext.eventChkInf[7] |= 2;    // dodongo
    gSaveContext.eventChkInf[7] |= 4;    // phantom ganon
    gSaveContext.eventChkInf[7] |= 8;    // volvagia
    gSaveContext.eventChkInf[7] |= 0x10; // morpha
    gSaveContext.eventChkInf[7] |= 0x20; // twinrova
    gSaveContext.eventChkInf[7] |= 0x40; // barinade
    gSaveContext.eventChkInf[7] |= 0x80; // bongo bongo

    static std::array<u8, 24> sItems = {
        ITEM_STICK,     ITEM_NUT,  ITEM_BOMB, ITEM_BOW,      ITEM_NONE,        ITEM_NONE,
        ITEM_SLINGSHOT, ITEM_NONE, ITEM_NONE, ITEM_LONGSHOT, ITEM_NONE,        ITEM_NONE,
        ITEM_BOOMERANG, ITEM_LENS, ITEM_NONE, ITEM_HAMMER,   ITEM_ARROW_LIGHT, ITEM_NONE,
        ITEM_NONE,      ITEM_NONE, ITEM_NONE, ITEM_NONE,     ITEM_NONE,        ITEM_NONE,
    };

    static std::array<s8, 16> sAmmo = { 5, 5, 10, 30, 0, 0, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    for (int item = 0; item < ARRAY_COUNT(gSaveContext.inventory.items); item++) {
        gSaveContext.inventory.items[item] = sItems[item];
    }

    for (int ammo = 0; ammo < ARRAY_COUNT(gSaveContext.inventory.ammo); ammo++) {
        gSaveContext.inventory.ammo[ammo] = sAmmo[ammo];
    }

    gSaveContext.inventory.equipment = 4947;
    gSaveContext.inventory.upgrades = 1196105;

    BossRush_SetEquipment(LINK_AGE_CHILD);
}

void BossRush_SetEquipment(uint8_t linkAge) {

    static std::array<u8, 8> sButtonItems;
    static std::array<u8, 7> sCButtonSlots;

    // Set Child Equipment. Used on save init.
    if (linkAge == LINK_AGE_CHILD) {
        sButtonItems = {
            ITEM_SWORD_KOKIRI, ITEM_STICK, ITEM_NUT, ITEM_BOMB, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE
        };

        sCButtonSlots = { SLOT_STICK, SLOT_NUT, SLOT_BOMB, SLOT_NONE, SLOT_NONE, SLOT_NONE, SLOT_NONE };

        gSaveContext.equips.equipment = 4369;
    // Set Adult equipment. Used when first 3 bosses are defeated and the player is set to adult.
    } else {
        sButtonItems = {
            ITEM_SWORD_MASTER, ITEM_BOW, ITEM_LONGSHOT, ITEM_HAMMER, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE
        };

        sCButtonSlots = { SLOT_BOW, SLOT_HOOKSHOT, SLOT_HAMMER, SLOT_NONE, SLOT_NONE, SLOT_NONE, SLOT_NONE };

        gSaveContext.equips.equipment = 4658;
    }

    // Button Items
    for (int button = 0; button < ARRAY_COUNT(gSaveContext.equips.buttonItems); button++) {
        gSaveContext.equips.buttonItems[button] = sButtonItems[button];
    }

    // C buttons
    for (int button = 0; button < ARRAY_COUNT(gSaveContext.equips.cButtonSlots); button++) {
        gSaveContext.equips.cButtonSlots[button] = sCButtonSlots[button];
    }
}
