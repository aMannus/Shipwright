#include "global.h"
#include "soh/Enhancements/enemyrandomizer.h"

extern "C" Actor* OTRActor_Spawn(ActorContext* actorCtx, PlayState* play, s16 actorId, f32 posX, f32 posY, f32 posZ,
                                 s16 rotX, s16 rotY, s16 rotZ, s16 params) {

    // Hack to remove enemies that wrongfully spawn because of bypassing object dependency with enemy randomizer on.
    // Remove bats and skulltulas from graveyard.
    // Remove octorok in lost woods.
    if (((actorId == ACTOR_EN_FIREFLY || (actorId == ACTOR_EN_SW && params == 0)) && play->sceneNum == SCENE_SPOT02) ||
        (actorId == ACTOR_EN_OKUTA && play->sceneNum == SCENE_SPOT10)) {
        return NULL;
    }

    // Hack to change a pot in Spirit Temple that holds a Deku Shield to not hold anything.
    // This Deku Shield doesn't normally spawn in authentic gameplay because of object dependency.
    if (actorId == ACTOR_OBJ_TSUBO && params == 24597) {
        params = 24067;
    }

    uint8_t tryRandomizeEnemy =
    CVar_GetS32("gRandomizedEnemies", 0) &&
    gSaveContext.fileNum >= 0 && gSaveContext.fileNum <= 2;

    if (tryRandomizeEnemy) {

        if (IsEnemyFoundToRandomize(play, actorId, params, posX)) {

            // When replacing Iron Knuckles in Spirit Temple, move them away from the throne because
            // some enemies can get stuck on the throne.
            if (actorId == ACTOR_EN_IK && play->sceneNum == SCENE_JYASINZOU) {
                if (params == 6657) {
                    posX = posX + 150;
                } else if (params == 6401) {
                    posX = posX - 150;
                }
            }

            // Do a raycast from the original position of the actor to find the ground below it, then try to place
            // the new actor on the ground. This way enemies don't spawn very high in the sky, and gives us control
            // over height offsets per enemy from a proven grounded position.
            CollisionPoly poly;
            Vec3f pos;
            f32 raycastResult;

            pos.x = posX;
            pos.y = posY + 50;
            pos.z = posZ;
            raycastResult = BgCheck_AnyRaycastFloor1(&play->colCtx, &poly, &pos);

            // If ground is found below actor, move actor to that height.
            if (raycastResult > BGCHECK_Y_MIN) {
                posY = raycastResult;
            }

            // Get randomized enemy ID and parameter.
            enemyEntry newEnemy = GetRandomizedEnemy(posX, posY, posZ);

            // While randomized enemy isn't allowed in certain situations, randomize again.
            while (!IsEnemyAllowedToSpawn(play, newEnemy)) {
                newEnemy = GetRandomizedEnemy(posX, posY, posZ);
            }

            actorId = newEnemy.enemyId;
            params = newEnemy.enemyParam;

            // Straighten out enemies so they aren't flipped on their sides when the original spawn is.
            rotX = 0;

            switch (actorId) {
                    // When spawning big jellyfish, spawn it up high.
                case ACTOR_EN_VALI:
                    posY = posY + 300;
                    break;
                    // Spawn peahat off the ground, otherwise it kills itself by colliding with the ground.
                case ACTOR_EN_PEEHAT:
                    if (params == 1) {
                        posY = posY + 100;
                    }
                    break;
                    // Spawn skulltulas off the ground.
                case ACTOR_EN_ST:
                    posY = posY + 200;
                    break;
                    // Spawn flying enemies off the ground.
                case ACTOR_EN_FIREFLY:
                case ACTOR_EN_BILI:
                case ACTOR_EN_BB:
                case ACTOR_EN_CLEAR_TAG:
                case ACTOR_EN_CROW:
                    posY = posY + 75;
                    break;
                default:
                    break;
            }
        }
    }

    return Actor_Spawn(actorCtx, play, actorId, posX, posY, posZ, rotX, rotY, rotZ, params);
}
