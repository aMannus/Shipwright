#include "leveled_overlays.h"
#include "global.h"
#include "textures/icon_item_static/icon_item_static.h"
#include "textures/parameter_static/parameter_static.h"
#include "textures/do_action_static/do_action_static.h"
#include "textures/icon_item_24_static/icon_item_24_static.h"
#include "textures/message_static/message_static.h"
#include "textures/nes_font_static/nes_font_static.h"



Gfx* Gfx_Texture32(Gfx* displayListHead, void* texture, s16 textureWidth, s16 textureHeight, s16 rectLeft, s16 rectTop,
                    s16 rectWidth, s16 rectHeight, u16 dsdx, u16 dtdy) {
    gDPLoadTextureBlock(displayListHead++, texture, G_IM_FMT_RGBA, G_IM_SIZ_32b, textureWidth, textureHeight, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    gSPWideTextureRectangle(displayListHead++, rectLeft << 2, rectTop << 2, (rectLeft + rectWidth) << 2,
                            (rectTop + rectHeight) << 2, G_TX_RENDERTILE, 0, 0, dsdx, dtdy);

    return displayListHead;
}

Gfx* Gfx_Texture4b(Gfx* displayListHead, void* texture, s16 textureWidth, s16 textureHeight, s16 rectLeft, s16 rectTop,
                   s16 rectWidth, s16 rectHeight, u16 dsdx, u16 dtdy) {
    gDPLoadTextureBlock_4b(displayListHead++, texture, G_IM_FMT_IA, textureWidth, textureHeight, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);

    gSPWideTextureRectangle(displayListHead++, rectLeft << 2, rectTop << 2, (rectLeft + rectWidth) << 2,
                            (rectTop + rectHeight) << 2, G_TX_RENDERTILE, 0, 0, dsdx, dtdy);

    return displayListHead;
}

void Leveled_DrawTexI8(PlayState* play, void* texture, s16 textureWidth, s16 textureHeight, s16 rectLeft,
                       s16 rectTop, s16 rectWidth, s16 rectHeight, u8 r, u8 g, u8 b) {

    OPEN_DISPS(play->state.gfxCtx);
    gDPPipeSync(POLY_KAL_DISP++);
    gDPSetTextureFilter(POLY_KAL_DISP++, G_TF_AVERAGE);
    gDPSetPrimColor(POLY_KAL_DISP++, 0, 0, r, g, b, play->pauseCtx.alpha);

    POLY_KAL_DISP = Gfx_TextureI8(POLY_KAL_DISP, texture, textureWidth, textureHeight, rectLeft, rectTop, rectWidth,
                                  rectHeight, 1 << 10, 1 << 10);

    CLOSE_DISPS(play->state.gfxCtx);
}

void Leveled_DrawTexIA8(PlayState* play, void* texture, s16 textureWidth, s16 textureHeight, s16 rectLeft,
                        s16 rectTop, s16 rectWidth, s16 rectHeight, u8 r, u8 g, u8 b) {

    OPEN_DISPS(play->state.gfxCtx);
    gDPPipeSync(POLY_KAL_DISP++);
    gDPSetTextureFilter(POLY_KAL_DISP++, G_TF_AVERAGE);
    gDPSetPrimColor(POLY_KAL_DISP++, 0, 0, r, g, b, play->pauseCtx.alpha);

    POLY_KAL_DISP = Gfx_TextureIA8(POLY_KAL_DISP, texture, textureWidth, textureHeight, rectLeft, rectTop, rectWidth,
                                   rectHeight, 1 << 10, 1 << 10);

    CLOSE_DISPS(play->state.gfxCtx);
}

void Leveled_DrawTex32(PlayState* play, void* texture, s16 textureWidth, s16 textureHeight, s16 rectLeft,
                       s16 rectTop, s16 rectWidth, s16 rectHeight) {

    OPEN_DISPS(play->state.gfxCtx);
    gDPPipeSync(POLY_KAL_DISP++);
    gDPSetTextureFilter(POLY_KAL_DISP++, G_TF_AVERAGE);
    gDPSetPrimColor(POLY_KAL_DISP++, 0, 0, 255, 255, 255, play->pauseCtx.alpha);

    POLY_KAL_DISP = Gfx_Texture32(POLY_KAL_DISP, texture, textureWidth, textureHeight, rectLeft, rectTop, rectWidth,
                                  rectHeight, 1 << 10, 1 << 10);

    CLOSE_DISPS(play->state.gfxCtx);
}

void Leveled_DrawTex4b(PlayState* play, void* texture, s16 textureWidth, s16 textureHeight, s16 rectLeft,
                       s16 rectTop, s16 rectWidth, s16 rectHeight) {

    OPEN_DISPS(play->state.gfxCtx);
    gDPPipeSync(POLY_KAL_DISP++);
    gDPSetTextureFilter(POLY_KAL_DISP++, G_TF_AVERAGE);
    gDPSetPrimColor(POLY_KAL_DISP++, 0, 0, 255, 255, 255, play->pauseCtx.alpha);

    POLY_KAL_DISP = Gfx_Texture4b(POLY_KAL_DISP, texture, textureWidth, textureHeight, rectLeft, rectTop, rectWidth,
                                  rectHeight, 1 << 10, 1 << 10);

    CLOSE_DISPS(play->state.gfxCtx);
}

void Leveled_OverlayDrawTex4b(PlayState* play, void* texture, s16 textureWidth, s16 textureHeight, s16 rectLeft,
                       s16 rectTop, s16 rectWidth, s16 rectHeight, u16 alpha) {

    OPEN_DISPS(play->state.gfxCtx);
    gDPPipeSync(OVERLAY_DISP++);
    gDPSetTextureFilter(OVERLAY_DISP++, G_TF_AVERAGE);
    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, alpha);

    OVERLAY_DISP = Gfx_Texture4b(OVERLAY_DISP, texture, textureWidth, textureHeight, rectLeft, rectTop, rectWidth,
                                  rectHeight, 1 << 10, 1 << 10);

    CLOSE_DISPS(play->state.gfxCtx);
}

void ActorDamageNumber_New(Actor* actor, u16 damage) {
    if (damage == 0)
        return;

    Vec2f position = { 0, 0 };
    Vec2f velocity = { 0, -8 };

    actor->floatingNumber[0] = damage;
    actor->floatingNumberLife[0] = 30;
    actor->floatingNumberPosition[0] = position;
    actor->floatingNumberVelocity[0] = velocity;
}

void ActorExperienceNumber_New(Actor* actor, u16 experience) {
    if (experience == 0)
        return;


    Vec2f position = { 0, 0 };
    Vec2f velocity = { 0, -6 };

    actor->floatingNumber[1] = experience;
    actor->floatingNumberLife[1] = 40;
    actor->floatingNumberPosition[1] = position;
    actor->floatingNumberVelocity[1] = velocity;
}

void ActorLevelUp_New(Actor* actor, u8 powerDiff, u8 courageDiff, u16 healthDiff, u8 magicDiff) {

    Vec2f position = { 0, 0 };
    Vec2f velocity = { 0, -6 };

    actor->floatingNumberLife[2] = 100;
    if (powerDiff > 0)
        actor->floatingNumberLife[3] = 100;
    if (courageDiff > 0)
        actor->floatingNumberLife[4] = 100;
    if (healthDiff > 0)
        actor->floatingNumberLife[5] = 100;
    if (magicDiff > 0)
        actor->floatingNumberLife[6] = 100;

    actor->floatingNumberPosition[2] = position;
    actor->floatingNumberVelocity[2] = velocity;
    position.x = 16;
    position.y = 0;
    velocity.x = -4;
    velocity.y = -5;
    actor->floatingNumberPosition[3] = position;
    actor->floatingNumberVelocity[3] = velocity;
    position.x = 16;
    position.y = 0;
    velocity.x = 4;
    velocity.y = -5;
    actor->floatingNumberPosition[4] = position;
    actor->floatingNumberVelocity[4] = velocity;
    position.x = 16;
    position.y = 0;
    velocity.x = -2;
    velocity.y = -5;
    actor->floatingNumberPosition[5] = position;
    actor->floatingNumberVelocity[5] = velocity;
    position.x = 16;
    position.y = 0;
    velocity.x = 2;
    velocity.y = -5;
    actor->floatingNumberPosition[6] = position;
    actor->floatingNumberVelocity[6] = velocity;
}

void ActorExperienceNumber_Draw(PlayState* play, Actor* actor) {

    extern const char* digitTextures[];
    s16 val = actor->floatingNumber[1];
    u8 digit[] = { 0, 0, 0, 0, 0 };
    u8 digits = 1;
    u8 width = 8;
    Vec3f spBC;
    f32 spB4;
    s32 j;

    if (actor->floatingNumberLife[1] <= 0)
        return;

    OPEN_DISPS(play->state.gfxCtx);

    // Digits
    if (val < 0)
        val = 0;

    if (val > 32000)
        val = 32000;

    if (val >= 10000)
        digits += 1;
    if (val >= 1000)
        digits += 1;
    if (val >= 100)
        digits += 1;
    if (val >= 10)
        digits += 1;

    for (j = 0; val >= 10000; j++) {
        val -= 10000;
        digit[4] += 1;
    }
    for (j = 0; val >= 1000; j++) {
        val -= 1000;
        digit[3] += 1;
    }
    for (j = 0; val >= 100; j++) {
        val -= 100;
        digit[2] += 1;
    }
    for (j = 0; val >= 10; j++) {
        val -= 10;
        digit[1] += 1;
    }
    digit[0] = (u8)val;

    // Velocity
    actor->floatingNumberPosition[1].x += actor->floatingNumberVelocity[1].x;
    actor->floatingNumberPosition[1].y += actor->floatingNumberVelocity[1].y;

    if (actor->floatingNumberVelocity[1].y < 0) {
        actor->floatingNumberVelocity[1].y += 0.4f;
    }

    // Life
    actor->floatingNumberLife[1]--;

    // Position
    func_8002BE04(play, &actor->world.pos, &spBC, &spB4);

    spBC.x = (160 * (spBC.x * spB4)) * 1.0f + 157 + actor->floatingNumberPosition[1].x + (digits - 1) * width / 2;
    spBC.x = CLAMP(spBC.x, -320.0f, 320.0f);

    spBC.y = (120 * (spBC.y * spB4)) * -1.0f + 90 + actor->floatingNumberPosition[1].y;
    spBC.y = CLAMP(spBC.y, -240.0f, 240.0f);

    if (spBC.z <= -0) {
        spBC.x = 160 + actor->floatingNumberPosition[1].x + (digits - 1) * width / 2;
        spBC.y = 200 + actor->floatingNumberPosition[1].y;
    }

    spBC.z = spBC.z * 1.0f;

    // Color
    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 190, 190, 0, 255);
    gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                      PRIMITIVE, 0);

    // Draw
    for (u8 i = 0; i < digits; i++) {
            OVERLAY_DISP = Gfx_TextureI8(OVERLAY_DISP, (u8*)digitTextures[digit[i]], 8, 16, (s16)spBC.x - i * width, (s16)spBC.y,
                                         8, 16, 1 << 10, 1 << 10);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void ActorDamageNumber_Draw(PlayState* play, Actor* actor) {

    extern const char* digitTextures[];
    s16 val = actor->floatingNumber[0];
    u8 digit[] = { 0, 0, 0 };
    u8 digits = 1;
    u8 width = 8;
    Vec3f spBC;
    f32 spB4;
    s32 j;

    if (actor->floatingNumberLife[0] <= 0)
        return;

    OPEN_DISPS(play->state.gfxCtx);

    // Digits
    if (val < 0)
        val = 0;

    if (val > 999)
        val = 999;

    if (val >= 100)
        digits += 1;
    if (val >= 10)
        digits += 1;

    for (j = 0; val >= 100; j++) {
        val -= 100;
        digit[2] += 1;
    }
    for (j = 0; val >= 10; j++) {
        val -= 10;
        digit[1] += 1;
    }
    digit[0] = (u8)val;

    // Velocity
    actor->floatingNumberPosition[0].x += actor->floatingNumberVelocity[0].x;
    actor->floatingNumberPosition[0].y += actor->floatingNumberVelocity[0].y;

    actor->floatingNumberVelocity[0].y += 2.0f;
    if (actor->floatingNumberPosition[0].y >= 0) {
        actor->floatingNumberPosition[0].y = 0;
        actor->floatingNumberVelocity[0].y = -actor->floatingNumberVelocity[0].y * 0.5f;
        if (actor->floatingNumberVelocity[0].y >= -4.0f)
            actor->floatingNumberVelocity[0].y = 0;
    }

    // Life
    actor->floatingNumberLife[0]--;

    // Position
    func_8002BE04(play, &actor->world.pos, &spBC, &spB4);

    spBC.x = (160 * (spBC.x * spB4)) * 1.0f + 157 + actor->floatingNumberPosition[0].x + (digits - 1) * width / 2;
    spBC.x = CLAMP(spBC.x, -320.0f, 320.0f);

    spBC.y = (120 * (spBC.y * spB4)) * -1.0f + 90 + actor->floatingNumberPosition[0].y;
    spBC.y = CLAMP(spBC.y, -240.0f, 240.0f);

    spBC.z = spBC.z * 1.0f;

    // Color
    if (actor->category == ACTORCAT_PLAYER) {
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 100, 0, 255);
    } else {
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, 255);
    }

    // Draw
    gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                      PRIMITIVE, 0);

    for (u8 i = 0; i < 3; i++) {
        if (i == 0 || i == 1 && (digit[1] > 0 || digit[2] > 0) || (i == 2 && digit[2] > 0))
            OVERLAY_DISP = Gfx_TextureI8(OVERLAY_DISP, (u8*)digitTextures[digit[i]], 8, 16, (s16)spBC.x - i * width, (s16)spBC.y,
                                         8, 16, 1 << 10, 1 << 10);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void Actor_LevelUpDraw(PlayState* play, Actor* actor) {
    u8 width = 8;
    Vec3f spBC;
    f32 spB4;
    for (s8 i = 2; i < 7; i++) {
        if (actor->floatingNumberLife[i] <= 0)
            continue;

        OPEN_DISPS(play->state.gfxCtx);

        // Velocity
        actor->floatingNumberPosition[i].x += actor->floatingNumberVelocity[i].x;
        actor->floatingNumberPosition[i].y += actor->floatingNumberVelocity[i].y;

        if (actor->floatingNumberVelocity[i].y < 0) {
            actor->floatingNumberVelocity[i].y += 0.75f;
            if (actor->floatingNumberVelocity[i].y > 0)
                actor->floatingNumberVelocity[i].y = 0;
        }
        if (actor->floatingNumberVelocity[i].x < 0) {
            actor->floatingNumberVelocity[i].x += 0.5f;
            if (actor->floatingNumberVelocity[i].x > 0)
                actor->floatingNumberVelocity[i].x = 0;
        }
        if (actor->floatingNumberVelocity[i].x > 0) {
            actor->floatingNumberVelocity[i].x -= 0.5f;
            if (actor->floatingNumberVelocity[i].x < 0)
                actor->floatingNumberVelocity[i].x = 0;
        }

        // Life
        actor->floatingNumberLife[i]--;

        // Position
        func_8002BE04(play, &actor->world.pos, &spBC, &spB4);

        spBC.x = (160 * (spBC.x * spB4)) * 1.0f + 165 + actor->floatingNumberPosition[i].x - 24;
        spBC.x = CLAMP(spBC.x, -320.0f, 320.0f);

        spBC.y = (120 * (spBC.y * spB4)) * -1.0f + 90 + actor->floatingNumberPosition[i].y;
        spBC.y = CLAMP(spBC.y, -240.0f, 240.0f);

        spBC.z = spBC.z * 1.0f;

        if (spBC.z < 0) {
            spBC.x = 160 + actor->floatingNumberPosition[i].x - 24;
            spBC.y = 200 + actor->floatingNumberPosition[i].y;
        }
        
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, 255);
        gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        if (i == 2) {
            OVERLAY_DISP = Gfx_TextureI8(OVERLAY_DISP, (u8*)gMsgChar4CLatinCapitalLetterLTex, 8, 16, -99, -99, 8, 16,
                                         1 << 10, 1 << 10);
            OVERLAY_DISP = Gfx_TextureI8(OVERLAY_DISP, (u8*)gMsgChar45LatinCapitalLetterETex, 8, 16, -99, -99, 8, 16,
                                         1 << 10, 1 << 10);
            OVERLAY_DISP = Gfx_TextureI8(OVERLAY_DISP, (u8*)gMsgChar56LatinCapitalLetterVTex, 8, 16, -99, -99, 8, 16,
                                         1 << 10, 1 << 10);
            OVERLAY_DISP = Gfx_TextureI8(OVERLAY_DISP, (u8*)gMsgChar55LatinCapitalLetterUTex, 8, 16, -99, -99, 8, 16,
                                         1 << 10, 1 << 10);
            OVERLAY_DISP = Gfx_TextureI8(OVERLAY_DISP, (u8*)gMsgChar50LatinCapitalLetterPTex, 8, 16, -99, -99, 8, 16,
                                         1 << 10, 1 << 10);

            for (u8 j = 0; j < 6; j++) {
                OVERLAY_DISP = Gfx_TextureI8(OVERLAY_DISP, (u8*)gMsgChar4CLatinCapitalLetterLTex, 8, 8, (s16)spBC.x, (s16)spBC.y,
                                             8, 8, 1 << 10, 1 << 10);
                OVERLAY_DISP = Gfx_TextureI8(OVERLAY_DISP, (u8*)gMsgChar45LatinCapitalLetterETex, 8, 8, (s16)spBC.x + 5,
                                             (s16)spBC.y, 8, 8, 1 << 10, 1 << 10);
                OVERLAY_DISP = Gfx_TextureI8(OVERLAY_DISP, (u8*)gMsgChar56LatinCapitalLetterVTex, 8, 8, (s16)spBC.x + 10,
                                             (s16)spBC.y, 8, 8, 1 << 10, 1 << 10);
                OVERLAY_DISP = Gfx_TextureI8(OVERLAY_DISP, (u8*)gMsgChar45LatinCapitalLetterETex, 8, 8, (s16)spBC.x + 15,
                                             (s16)spBC.y, 8, 8, 1 << 10, 1 << 10);
                OVERLAY_DISP = Gfx_TextureI8(OVERLAY_DISP, (u8*)gMsgChar4CLatinCapitalLetterLTex, 8, 8, (s16)spBC.x + 20,
                                             (s16)spBC.y, 8, 8, 1 << 10, 1 << 10);
                OVERLAY_DISP = Gfx_TextureI8(OVERLAY_DISP, (u8*)gMsgChar55LatinCapitalLetterUTex, 8, 8, (s16)spBC.x + 30,
                                             (s16)spBC.y, 8, 8, 1 << 10, 1 << 10);
                OVERLAY_DISP = Gfx_TextureI8(OVERLAY_DISP, (u8*)gMsgChar50LatinCapitalLetterPTex, 8, 8, (s16)spBC.x + 35,
                                             (s16)spBC.y, 8, 8, 1 << 10, 1 << 10);
            }
        }

        if (i == 3) {
            OVERLAY_DISP =
                Gfx_Texture32(OVERLAY_DISP, (u8*)gSilverGauntletsIconTex, 32, 32, -99, -99, 32, 32, 1 << 10, 1 << 10);

            OVERLAY_DISP = Gfx_Texture32(OVERLAY_DISP, (u8*)gSilverGauntletsIconTex, 8, 8, (s16)spBC.x, (s16)spBC.y, 8, 8,
                                         1 << 10, 1 << 10);
        }
        if (i == 4) {
            OVERLAY_DISP =
                Gfx_Texture32(OVERLAY_DISP, (u8*)gHylianShieldIconTex, 32, 32, -99, -99, 32, 32, 1 << 10, 1 << 10);

            OVERLAY_DISP =
                Gfx_Texture32(OVERLAY_DISP, (u8*)gHylianShieldIconTex, 8, 8, (s16)spBC.x, (s16)spBC.y, 8, 8,
                                         1 << 10, 1 << 10);
        }
        if (i == 5) {

            gDPPipeSync(OVERLAY_DISP++);
            gDPSetTextureFilter(OVERLAY_DISP++, G_TF_AVERAGE);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 70, 0, 255);

            OVERLAY_DISP =
                Gfx_TextureIA8(OVERLAY_DISP, (u8*)gHeartFullTex, 16, 16, -99, -99, 16, 16, 1 << 10, 1 << 10);

            OVERLAY_DISP =
                Gfx_TextureIA8(OVERLAY_DISP, (u8*)gHeartFullTex, 8, 8, (s16)spBC.x, (s16)spBC.y, 8, 8,
                                         1 << 10, 1 << 10);
        }

        if (i == 6) {
            OVERLAY_DISP =
                Gfx_Texture32(OVERLAY_DISP, (u8*)gBigMagicJarIconTex, 24, 24, -99, -99, 24, 24, 1 << 10, 1 << 10);

            OVERLAY_DISP = Gfx_Texture32(OVERLAY_DISP, (u8*)gBigMagicJarIconTex, 8, 8, (s16)spBC.x, (s16)spBC.y, 24, 24,
                                         1 << 10, 1 << 10); 
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

extern const char* _gAmmoDigit0Tex[];
void Leveled_ValueNumberDraw(PlayState* play, u16 x, u16 y, u32 value, u8 r, u8 g, u8 b) {
    s32 val;
    u8 digit[] = { 0, 0, 0, 0, 0, 0 };
    s16 separation = 5;

    u8 digits;

    OPEN_DISPS(play->state.gfxCtx);

    val = value;

        if (val > 999999)
            val = 999999;

    if (val < 0)
        val = 0;

    gDPPipeSync(POLY_KAL_DISP++);
    gDPSetTextureFilter(POLY_KAL_DISP++, G_TF_AVERAGE);

    gDPSetPrimColor(POLY_KAL_DISP++, 0, 0, r, g, b, play->pauseCtx.alpha);

    digits = 1;

    if (val >= 100000)
        digits += 1;
    if (val >= 10000)
        digits += 1;
    if (val >= 1000)
        digits += 1;
    if (val >= 100)
        digits += 1;
    if (val >= 10)
        digits += 1;

    s8 j;

    for (j = 0; val >= 100000; j++) {
        val -= 100000;
        digit[5] += 1;
    }
    for (j = 0; val >= 10000; j++) {
        val -= 10000;
        digit[4] += 1;
    }
    for (j = 0; val >= 1000; j++) {
        val -= 1000;
        digit[3] += 1;
    }
    for (j = 0; val >= 100; j++) {
        val -= 100;
        digit[2] += 1;
    }
    for (j = 0; val >= 10; j++) {
        val -= 10;
        digit[1] += 1;
    }
    digit[0] = val;

    gDPPipeSync(POLY_KAL_DISP++);

    for (s8 i = 0; i < digits; i++) {
        POLY_KAL_DISP =
            Gfx_TextureIA8(POLY_KAL_DISP, (u8*)_gAmmoDigit0Tex[digit[i]], 8, 8, x - i * 6 + 6 * (digits - 1), y, 8,
                                     8, 1 << 10, 1 << 10);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void Leveled_BigValueNumberDraw(PlayState* play, u16 x, u16 y, u32 value, u8 r, u8 g, u8 b, u8 a) {
    s32 val;
    u8 digit[] = { 0, 0, 0, 0, 0, 0 };
    s16 separation = 5;
    u8 width = 7;

    extern const char* digitTextures[];

    u8 digits;

    OPEN_DISPS(play->state.gfxCtx);

    val = value;

        if (val > 999999)
            val = 999999;

    if (val < 0)
        val = 0;

    gDPPipeSync(POLY_KAL_DISP++);
    gDPSetTextureFilter(POLY_KAL_DISP++, G_TF_AVERAGE);

    gDPSetPrimColor(POLY_KAL_DISP++, 0, 0, r, g, b, a);

    digits = 1;

    if (val >= 100000)
        digits += 1;
    if (val >= 10000)
        digits += 1;
    if (val >= 1000)
        digits += 1;
    if (val >= 100)
        digits += 1;
    if (val >= 10)
        digits += 1;

    s8 j;

    for (j = 0; val >= 100000; j++) {
        val -= 100000;
        digit[5] += 1;
    }
    for (j = 0; val >= 10000; j++) {
        val -= 10000;
        digit[4] += 1;
    }
    for (j = 0; val >= 1000; j++) {
        val -= 1000;
        digit[3] += 1;
    }
    for (j = 0; val >= 100; j++) {
        val -= 100;
        digit[2] += 1;
    }
    for (j = 0; val >= 10; j++) {
        val -= 10;
        digit[1] += 1;
    }
    digit[0] = val;

    gDPPipeSync(POLY_KAL_DISP++);

    for (u8 i = 0; i < digits; i++) {
        gDPSetPrimColor(POLY_KAL_DISP++, 0, 0, 0, 0, 0, 255);

        for (j = 0; j < 4; j++) {
            POLY_KAL_DISP = Gfx_TextureI8(POLY_KAL_DISP, (u8*)digitTextures[digit[i]], 8, 16, x - i * width + width * (digits - 1) + (j % 2) * 2 - 1, y + (j / 2) * 2 - 1, 8, 16, 1 << 10, 1 << 10);
        }

        gDPSetPrimColor(POLY_KAL_DISP++, 0, 0, 255, 255, 255, 255);
        POLY_KAL_DISP = Gfx_TextureI8(POLY_KAL_DISP, (u8*)digitTextures[digit[i]], 8, 16, x - i * width + width * (digits - 1), y, 8, 16, 1 << 10, 1 << 10);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void Leveled_KaleidoEquip_Stats(PlayState* play) {
    extern const char* digitTextures[];
    Player* player = GET_PLAYER(play);
    u16 statY = 70;
    u8 attack = 1;
    if (CUR_EQUIP_VALUE(EQUIP_SWORD) == 1)
        attack = HEALTH_ATTACK_MULTIPLIER;
    if (CUR_EQUIP_VALUE(EQUIP_SWORD) == 2)
        attack = HEALTH_ATTACK_MULTIPLIER << 1;
    if (CUR_EQUIP_VALUE(EQUIP_SWORD) == 3) {
        attack = HEALTH_ATTACK_MULTIPLIER << 2;
        if (gBitFlags[3] & gSaveContext.inventory.equipment)
            attack = HEALTH_ATTACK_MULTIPLIER;
    }

    // Initialize textures
        Leveled_DrawTexIA8(play, (u8*)gMsgChar4CLatinCapitalLetterLTex, 8, 16, -114, -222, 8, 16, 255, 255, 255);
        Leveled_DrawTexIA8(play, (u8*)gMsgChar76LatinSmallLetterVTex, 8, 16, -114, -222, 8, 16, 255, 255, 255);
        Leveled_DrawTexIA8(play, (u8*)gMsgChar2BPlusSignTex, 8, 16, -114, -222, 8, 16, 255, 255, 255);
        Leveled_DrawTexIA8(play, (u8*)gMsgChar2DHyphenMinusTex, 8, 16, -114, -222, 8, 16, 255, 255, 255);
    
    Leveled_DrawTex32(play, (u8*)gKokiriSwordIconTex, 32, 32, -192, -268, 32, 32);
    Leveled_DrawTex32(play, (u8*)gSilverGauntletsIconTex, 32, 32, -192, -268, 32, 32);
    Leveled_DrawTex32(play, (u8*)gHylianShieldIconTex, 32, 32, -192, -268, 32, 32);
    Leveled_DrawTexIA8(play, (u8*)gHeartFullTex, 16, 16, -114, -222, 16, 16, 255, 255, 255);
    Leveled_DrawTex32(play, (u8*)gBigMagicJarIconTex, 24, 24, -114, -222, 24, 24);
    Leveled_DrawTexI8(play, (u8*)digitTextures[1], 8, 16, -114, -222, 8, 16, 255, 255, 255);
    Leveled_DrawTex32(play, (u8*)gGoronsBraceletIconTex, 32, 32, -192, -268, 32, 32);
    Leveled_DrawTex4b(play, (u8*)gNextDoActionENGTex, 48, 16, -192, -268, 48, 16);

    // Values and Icons
    // Level
    for (u8 i = 0; i < 10; i++) {
        Leveled_DrawTexIA8(play, (u8*)gMsgChar4CLatinCapitalLetterLTex, 8, 8, 92, statY, 8, 16, 255, 255, 255);
        Leveled_DrawTexIA8(play, (u8*)gMsgChar76LatinSmallLetterVTex, 8, 8, 95, statY, 8, 16, 255, 255, 255);
    }
    Leveled_BigValueNumberDraw(play, 100, statY - 6, player->actor.level, 255, 255, 255, 255);
    statY += 10;
    // Health
    Leveled_DrawTexIA8(play, (u8*)gHeartFullTex, 8, 8, 92, statY, 16, 16, 255, 70, 0);
    Leveled_DrawTexI8(play, (u8*)digitTextures[1], 8, 11, 116, statY - 2, 8, 16, 255, 255, 255);
    Leveled_ValueNumberDraw(play, 100, statY, gSaveContext.health, 255, 255, 255);
    Leveled_ValueNumberDraw(play, 123, statY, gSaveContext.healthCapacity2, 120, 255, 0);
    statY += 8;
    // Magic
    if (gSaveContext.magicCapacity > 0) {
        Leveled_DrawTex32(play, (u8*)gBigMagicJarIconTex, 8, 8, 92, statY, 24, 24);
        Leveled_DrawTexI8(play, (u8*)digitTextures[1], 8, 11, 116, statY - 2, 8, 16, 255, 255, 255);
        Leveled_ValueNumberDraw(play, 100, statY, gSaveContext.magic, 255, 255, 255);
        Leveled_ValueNumberDraw(play, 123, statY, gSaveContext.magicCapacity, 120, 255, 0);
        statY += 8;
    }
    // Attack
    Leveled_DrawTex32(play, (u8*)gKokiriSwordIconTex, 10, 12, 90, statY - 1, 10, 8);
    Leveled_ValueNumberDraw(play, 100, statY, GetActorStat_Attack(attack, player->actor.power + player->actor.powerModifier), 255, 255, 255);
    statY += 8;
    // Power
    Leveled_DrawTex32(play, (u8*)gSilverGauntletsIconTex, 8, 7, 92, statY, 8, 7);
    Leveled_ValueNumberDraw(play, 100, statY, player->actor.power, 255, 255, 255);
    if (player->actor.powerModifier > 0){
        for (u8 i = 0; i < 10; i++) {
            Leveled_DrawTexIA8(play, (u8*)gMsgChar2BPlusSignTex, 8, 8, 114, statY, 8, 16, 120, 255, 0);
        }
        Leveled_ValueNumberDraw(play, 118, statY, player->actor.powerModifier, 120, 255, 0);
    } else if (player->actor.powerModifier < 0){
        for (u8 i = 0; i < 10; i++) {
            Leveled_DrawTexIA8(play, (u8*)gMsgChar2DHyphenMinusTex, 8, 8, 114, statY, 8, 16, 255, 0, 0);
        }
        Leveled_ValueNumberDraw(play, 118, statY, -player->actor.powerModifier, 255, 0, 0);
    }
    statY += 8;
    // Courage
    Leveled_DrawTex32(play, (u8*)gHylianShieldIconTex, 8, 7, 92, statY, 8, 7);
    Leveled_ValueNumberDraw(play, 100, statY, player->actor.courage, 255, 255, 255);
    if (player->actor.courageModifier > 0){
        for (u8 i = 0; i < 10; i++) {
            Leveled_DrawTexIA8(play, (u8*)gMsgChar2BPlusSignTex, 8, 8, 114, statY, 8, 16, 120, 255, 0);
        }
        Leveled_ValueNumberDraw(play, 118, statY, player->actor.courageModifier, 120, 255, 0);
    } else if (player->actor.courageModifier < 0){
        for (u8 i = 0; i < 10; i++) {
            Leveled_DrawTexIA8(play, (u8*)gMsgChar2DHyphenMinusTex, 8, 8, 114, statY, 8, 16, 255, 0, 0);
        }
        Leveled_ValueNumberDraw(play, 118, statY, -player->actor.courageModifier, 255, 0, 0);
    }
    statY += 67;
    if (gSaveContext.magicCapacity > 0) {
        statY -= 8;
    }
    // EXP
    Leveled_DrawTex32(play, (u8*)gGoronsBraceletIconTex, 8, 7, 92, statY, 10, 7);
    Leveled_ValueNumberDraw(play, 100, statY, gSaveContext.experience, 255, 255, 255);
    statY += 8;
    // Next LV
    Leveled_DrawTex4b(play, (u8*)gNextDoActionENGTex, 24, 10, 84, statY, 24, 7);
    Leveled_ValueNumberDraw(play, 112, statY,
                            GetActorStat_NextLevelExp(player->actor.level, gSaveContext.experience), 255, 255, 255);
}

void Leveled_Interface_DrawNextLevel(PlayState* play) {
    if (gSaveContext.showNeededExpTimer > 0){
        gSaveContext.showNeededExpTimer--;
    } else {
        return;
    }

    Player* player = GET_PLAYER(play);
    u16 posX = OTRGetRectDimensionFromLeftEdge(10);
    u16 posY = 58;
    extern const char* digitTextures[];
    s32 val = GetActorStat_NextLevelExp(player->actor.level, gSaveContext.experience);
    u8 digit[] = { 0, 0, 0, 0, 0, 0 };
    u8 digits = 1;
    u8 width = 8;
    s32 j;

    Leveled_OverlayDrawTex4b(play, (u8*)gNextDoActionENGTex, 48, 16, -192, -268, 48, 16, 255 - play->pauseCtx.alpha); // Load texture
    Leveled_OverlayDrawTex4b(play, (u8*)gNextDoActionENGTex, 48, 16, posX, posY, 48, 16, 255 - play->pauseCtx.alpha); // Draw texture

    OPEN_DISPS(play->state.gfxCtx);

    // Digits
    if (val < 0)
        val = 0;

    if (val > 999999)
        val = 999999;

    if (val >= 100000)
        digits += 1;
    if (val >= 10000)
        digits += 1;
    if (val >= 1000)
        digits += 1;
    if (val >= 100)
        digits += 1;
    if (val >= 10)
        digits += 1;

    for (j = 0; val >= 100000; j++) {
        val -= 100000;
        digit[5] += 1;
    }
    for (j = 0; val >= 10000; j++) {
        val -= 10000;
        digit[4] += 1;
    }
    for (j = 0; val >= 1000; j++) {
        val -= 1000;
        digit[3] += 1;
    }
    for (j = 0; val >= 100; j++) {
        val -= 100;
        digit[2] += 1;
    }
    for (j = 0; val >= 10; j++) {
        val -= 10;
        digit[1] += 1;
    }
    digit[0] = (u8)val;

    // Color

    // Draw
    gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                      PRIMITIVE, 0);

    s16 numbersPosX = 38;

    for (u8 i = 0; i < digits; i++) {
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, 255 - play->pauseCtx.alpha);

        for (j = 0; j < 4; j++) {
            OVERLAY_DISP = Gfx_TextureI8(OVERLAY_DISP, (u8*)digitTextures[digit[i]], 8, 16, posX - i * width + width * (digits - 1) + numbersPosX + (j % 2) * 2 - 1, posY + (j / 2) * 2 - 1, 8, 16, 1 << 10, 1 << 10);
        }

        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, 255 - play->pauseCtx.alpha);
        OVERLAY_DISP = Gfx_TextureI8(OVERLAY_DISP, (u8*)digitTextures[digit[i]], 8, 16, posX - i * width + width * (digits - 1) + numbersPosX, posY, 8, 16, 1 << 10, 1 << 10);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}