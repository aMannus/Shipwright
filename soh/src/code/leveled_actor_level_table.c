#include "global.h"

/////////////////////////////////////////////////
//////////////////  BOSSES  /////////////////////
/////////////////////////////////////////////////
void Leveled_Gohma(PlayState* play, Actor*actor) {
    actor->level = 7;
    actor->exp = 120;
    
    if (actor->category == ACTORCAT_ENEMY) { // Larva
        actor->level = 5;
        if (actor->params < 10) {
            actor->exp = 5;
        }
    }
}

void Leveled_Dodongo(PlayState* play, Actor*actor) {
    if (actor->category == ACTORCAT_BOSS) { // King Dodongo
        actor->level = 15;
        actor->exp = 500;
    } else {
        actor->level = 14;
        actor->exp = 18;
    }
}

void Leveled_Barinade(PlayState* play, Actor*actor) {
    actor->level = 21;
    if (actor->params == -1) { // Body
        actor->exp = 850;
    }
}

void Leveled_PhantomGanon(PlayState* play, Actor* actor) {
    actor->level = 28;
    if (actor->params == 1)
        actor->exp = 1400;
}

void Leveled_Volvagia(PlayState* play, Actor* actor) {
    actor->level = 35;
    if (actor->id == ACTOR_BOSS_FD2)
        actor->exp = 2475;
}

void Leveled_Morpha(PlayState* play, Actor* actor) {
    actor->level = 40;
    actor->exp = 3500;
}

void Leveled_BongoBongo(PlayState* play, Actor* actor) {
    actor->level = 45;
    actor->exp = 4666;
}

void Leveled_Twinrova(PlayState* play, Actor* actor) {
    actor->level = 52;
    if (actor->params == 2)
        actor->exp = 6000;
}

void Leveled_Ganondorf(PlayState* play, Actor* actor) {
    actor->level = 62;
    actor->exp = 9999;
}

void Leveled_Ganon(PlayState* play, Actor* actor) {
    actor->level = 66;
}

/////////////////////////////////////////////////
///////////////  MINI-BOSSES  ///////////////////
/////////////////////////////////////////////////
void Leveled_BigOctorock(PlayState* play, Actor*actor) {
    actor->level = 20;
    actor->exp = 320;
}

void Leveled_FlareDancer(PlayState* play, Actor* actor) {
    actor->level = 34;
    if (actor->id == ACTOR_EN_FW) {
        actor->exp = 1000;
    }
}

void Leveled_DarkLink(PlayState* play, Actor* actor) {
    actor->level = GET_PLAYER(play)->actor.level;
    actor->exp = (u16)((f32)GetPlayerStat_NextLevelExpAtLevel(GET_PLAYER(play)->actor.level) * 0.50f);
}

void Leveled_DeadHand(PlayState* play, Actor* actor) {
    actor->level = 44;

    if (actor->id == ACTOR_EN_DH)
        actor->exp = 2465;
}

void Leveled_IronKnuckle(PlayState* play, Actor* actor) {
    actor->level = 50;
    actor->exp = 2733;
    if (actor->params == 0) {
        actor->level = 52;
        actor->exp = 3100;
    } 
    if (play->sceneNum == SCENE_GANONTIKA || play->sceneNum == SCENE_GANON) { // Ganon's Castle
        actor->level = 55;
        actor->exp = 2850;
    }
}
/////////////////////////////////////////////////
//////////////  NORMAL ENEMIES  /////////////////
/////////////////////////////////////////////////
void Leveled_Dekubaba(PlayState* play, Actor*actor) {
    if (actor->params == 1) { // Big baba
        actor->level = 24;
        actor->exp = 32;
        if (LINK_IS_CHILD) {
            actor->level = 5;
            actor->exp = 8;
        }
    } else {
        actor->level = 2;
        actor->exp = 3;
        if (play->sceneNum == SCENE_BMORI1) { // Forest Temple
            actor->level = 23;
            actor->exp = 19;
        }
    }
}

void Leveled_StickDekuBaba(PlayState* play, Actor*actor) {
    actor->level = 1;
    actor->exp = 1;
}

void Leveled_Skulltula(PlayState* play, Actor*actor) {
    actor->level = 3;
    actor->exp = 3;
    if (play->sceneNum == SCENE_BMORI1) { // Forest Temple
        actor->level = 21;
        actor->exp = 19;
    }
    if (play->sceneNum == SCENE_HAKADANCH ||
        play->sceneNum == SCENE_HAKADAN) { // Bottom of the Well and Shadow Temple
        actor->level = 38;
        actor->exp = 30;
    } else if (play->sceneNum == SCENE_JYASINZOU) { // Spirit Temple
        actor->level = 44;
        actor->exp = 34;
    } else if (play->sceneNum == SCENE_GANONTIKA || play->sceneNum == SCENE_GANON) { // Ganon's Castle
        actor->level = 50;
        actor->exp = 50;
    }
    if (actor->params == 1) { // Big
        actor->level += 3;
        actor->exp += 2;
    }
}

void Leveled_Wall_Skulltula(PlayState* play, Actor* actor) {
    if (((play, actor->params & 0xE000) >> 0xD) != 0) { // Gold Skulltula
        actor->level = gSaveContext.inventory.gsTokens + 1;
        actor->exp = 0;
    } else {
        actor->level = 3;
        actor->exp = 2;
        if (play->sceneNum == SCENE_BMORI1) { // Forest Temple
            actor->level = 24;
            actor->exp = 18;
        }
    }
}

void Leveled_DekuScrub(PlayState* play, Actor*actor) {
    actor->level = 8;
    actor->exp = 7;
}

void Leveled_Tektite(PlayState* play, Actor*actor) {
    if (actor->params == -2) { // Blue
        actor->level = 12;
        actor->exp = 12;
        if (LINK_IS_ADULT) {
            actor->level = 25;
            actor->exp = 21;
        }
        if (play->sceneNum == SCENE_MIZUSIN) { // Water Temple
            actor->level = 36;
            actor->exp = 44;
        }
    } else {
        actor->level = 9;
        actor->exp = 9;
        if (LINK_IS_ADULT) {
            actor->level = 27;
            actor->exp = 24;
        }
    }
}

void Leveled_Guay(PlayState* play, Actor*actor) {
    actor->level = 8;
    actor->exp = 4;
    if (LINK_IS_ADULT) {
        actor->level = 21;
        actor->exp = 13;
    }
}

void Leveled_Octorock(PlayState* play, Actor*actor) {
    actor->level = 13;
    actor->exp = 12;
    if (actor->params != 0) {
        actor->level = 0;
        actor->exp = 0;
    }
}

void Leveled_Armos(PlayState* play, Actor* actor) {
    actor->level = 12;
    actor->exp = 17;
    if (play->sceneNum == SCENE_JYASINZOU) { // Spirit Temple
        actor->level = 45;
        actor->exp = 60;
    } else if (play->sceneNum == SCENE_GANONTIKA || play->sceneNum == SCENE_GANON) { // Ganon's Castle
        actor->level = 50;
        actor->exp = 70;
    }
}

void Leveled_BabyDodongo(PlayState* play, Actor*actor) {
    actor->level = 11;
    actor->exp = 7;
}

void Leveled_Keese(PlayState* play, Actor*actor) {
    if (actor->params == 4) { // Ice Keese
        actor->level = 34;
        actor->exp = 33;
    } else {
        actor->level = 9;
        actor->exp = 5;

        if (play->sceneNum == SCENE_HIDAN) { // Fire Temple
            actor->level = 28;
            actor->exp = 22;
        } else if (play->sceneNum == SCENE_ICE_DOUKUTO) { // Ice Cavern
            actor->level = 31;
            actor->exp = 26;
        } else if (play->sceneNum == SCENE_MIZUSIN) { // Water Temple
            actor->level = 34;
            actor->exp = 29;
        } else if (play->sceneNum == SCENE_JYASINZOU) { // Spirit Temple
            actor->level = 42;
            actor->exp = 36;
        } else if (play->sceneNum == SCENE_HAKADANCH ||
            play->sceneNum == SCENE_HAKADAN) { // Bottom of the Well and Shadow Temple
            actor->level = 38;
            actor->exp = 33;
        } else if (play->sceneNum == SCENE_GANONTIKA || play->sceneNum == SCENE_GANON) { // Ganon's Castle
            actor->level = 50;
            actor->exp = 38;
        }
        if (play->sceneNum == SCENE_MEN) {
            actor->level = 55;
            actor->exp = 44;
        }
    }
}

void Leveled_Peahat(PlayState* play, Actor*actor) {
    actor->level = 18;
    actor->exp = 47;
    if (actor->params == 1) { // Larva
        actor->level = 13;
    }
}
void Leveled_Poh(PlayState* play, Actor*actor) {
    actor->level = 10;
    actor->exp = 14;
    if (actor->params == 2 || actor->params == 3) { // Composer
        actor->level = 15;
        actor->exp = 25;
    }
}

void Leveled_Poh_Field(PlayState* play, Actor*actor) {
    actor->level = 24;
    actor->exp = 25;
}

void Leveled_ReDead(PlayState* play, Actor*actor) {
    if (actor->params >= -1) {
        actor->level = 25;
        actor->exp = 45;
        if (play->sceneNum == SCENE_HAKADANCH || play->sceneNum == SCENE_HAKADAN) { // Bottom of the Well and Shadow Temple
            actor->level = 42;
            actor->exp = 171;
        } else if (play->sceneNum == SCENE_GANON_SONOGO || play->sceneNum == SCENE_GANONTIKA_SONOGO) {
            actor->level = 50;
            actor->exp = 230;
        }
    } else { // Gibdo
        actor->level = 43;
        actor->exp = 183;
    }
}

void Leveled_Shabom(PlayState* play, Actor*actor) {
    actor->level = 15;
}

void Leveled_Bari(PlayState* play, Actor*actor) {
    actor->level = 18;
    actor->exp = 25;
}

void Leveled_Biri(PlayState* play, Actor*actor) {
    actor->level = 16;
    actor->exp = 17;
}

void Leveled_Stinger(PlayState* play, Actor*actor) {
    actor->level = 17;
    actor->exp = 19;
    if (play->sceneNum == SCENE_MIZUSIN) { // Water Temple
        actor->level = 37;
        actor->exp = 85;
    }
}

void Leveled_JabuTentacle(PlayState* play, Actor*actor) {
    actor->level = 19;
    if (actor->params < 3) {
        actor->exp = 61;
    }
}

void Leveled_Tailpasaran(PlayState* play, Actor*actor) {
    actor->level = 19;
    actor->exp = 22;
}

void Leveled_Stalchild(PlayState* play, Actor*actor) {
    actor->level = 6 + (u16)(play, actor->params / 2);
    actor->exp = 3 + (u16)(play, actor->params / 2.5);
}

void Leveled_Beamos(PlayState* play, Actor*actor) {
    if (actor->params == 0) { // Big
        actor->level = 48;
        actor->exp = 90;
    } else {
        actor->level = 11;
        actor->exp = 17;
        if (play->sceneNum == SCENE_HAKADANCH ||
            play->sceneNum == SCENE_HAKADAN) { // Bottom of the Well and Shadow Temple
            actor->level = 43;
            actor->exp = 80;
        } else if (play->sceneNum == SCENE_JYASINZOU) { // Spirit Temple
            actor->level = 47;
            actor->exp = 87;
        } else if (play->sceneNum == SCENE_GANONTIKA || play->sceneNum == SCENE_GANON) { // Ganon's Castle
            actor->level = 50;
            actor->exp = 90;
        } else if (play->sceneNum == SCENE_MEN) {
            actor->level = 55;
            actor->exp = 120;
        }
    }
}

void Leveled_Wolfos(PlayState* play, Actor* actor) {
    if (actor->params == 0) {
        actor->level = 10;
        actor->exp = 24;
        if (LINK_IS_ADULT) {
            actor->level = 20;
            actor->exp = 29;
        }
        if (play->sceneNum == SCENE_BMORI1) { // Forest Temple
            actor->level = 26;
            actor->exp = 43;
        } else if (play->sceneNum == SCENE_JYASINZOU) { // Spirit Temple
            actor->level = 47;
            actor->exp = 158;
        } else if (play->sceneNum == SCENE_GANONTIKA || play->sceneNum == SCENE_GANON) { // Ganon's Castle
            actor->level = 50;
            actor->exp = 165;
        }
    } else { // White
        actor->level = 37;
        actor->exp = 126;
    }
    if (play->sceneNum == SCENE_MEN) {
        actor->level = 55;
        actor->exp = 270;
    }
}

void Leveled_Lizalfos(PlayState* play, Actor*actor) {
    if (actor->params == -2) { // Dinolfos
        actor->level = 52;
        actor->exp = 250;
    } else if (actor->params == -1) { // Lizalfos
        actor->level = 47;
        actor->exp = 210;
    } else { // Miniboss Lizalfos
        actor->level = 13;
        actor->exp = 140;
        actor->ignoreExpReward = true;
    }
    if (play->sceneNum == SCENE_MEN) {
        actor->level = 55;
        actor->exp = 320;
    }
}

void Leveled_Moblins(PlayState* play, Actor*actor) {
    if (actor->params == -1) { // Spear
        actor->level = 24;
        actor->exp = 32;
    } else if (actor->params == 0) { // Club
        actor->level = 25;
        actor->exp = 47;
    } else { // Spear patrol
        actor->level = 24;
        actor->exp = 24;
    }
}

void Leveled_Bubble(PlayState* play, Actor*actor) {
    if (actor->params == -1) { // Blue
        actor->level = 25;
        actor->exp = 29;
    } else if (actor->params == -2) { // Red
        actor->level = 32;
        actor->exp = 47;
        if ( play->sceneNum == SCENE_HAKADAN) { // Shadow Temple
            actor->level = 40;
            actor->exp = 75;
        }
    } else if (actor->params == -3) { // White
        actor->level = 45;
        actor->exp = 76;
    } else if (actor->params == -4) { // Big Green
        actor->level = 41;
        actor->exp = 82;
    } else { // Green
        actor->level = 26;
        actor->exp = 31;
        if (play->sceneNum == SCENE_HAKADANCH ||
            play->sceneNum == SCENE_HAKADAN) { // Bottom of the Well and Shadow Temple
            actor->level = 41;
            actor->exp = 70;
        } else if (play->sceneNum == SCENE_JYASINZOU) { // Spirit Temple
            actor->level = 45;
            actor->exp = 77;
        } else if (play->sceneNum == SCENE_GANONTIKA || play->sceneNum == SCENE_GANON) { // Ganon's Castle
            actor->level = 50;
            actor->exp = 85;
        }
    }
    if (play->sceneNum == SCENE_MEN) {
        actor->level = 55;
        actor->exp = 100;
    }
}

void Leveled_Stalfos(PlayState* play, Actor*actor) {
    actor->level = 27;
    actor->exp = 64;

    if (play->sceneNum == SCENE_BMORI1) { // Forest Temple
        actor->ignoreExpReward = true;
        actor->exp = 250;
    }else if (play->sceneNum == SCENE_HAKADAN) { // Shadow Temple
        actor->level = 43;
        actor->exp = 214;
    } else if (play->sceneNum == SCENE_JYASINZOU) { // Spirit Temple
        actor->level = 48;
        actor->exp = 236;
    } else if (play->sceneNum == SCENE_GANONTIKA || play->sceneNum == SCENE_GANON ||
               play->sceneNum == SCENE_GANON_SONOGO ||
               play->sceneNum == SCENE_GANONTIKA_SONOGO) { // Ganon's Castle
        actor->level = 50;
        actor->exp = 260;
    } else if (play->sceneNum == SCENE_MEN) {
        actor->level = 55;
        actor->exp = 345;
    }
}

void Leveled_Floormaster(PlayState* play, Actor*actor) {
    actor->level = 26;
    actor->exp = 41;
    actor->ignoreExpReward = true;
    if (play->sceneNum == SCENE_HAKADANCH ||
        play->sceneNum == SCENE_HAKADAN) { // Bottom of the Well and Shadow Temple
        actor->level = 42;
        actor->exp = 140;
    } else if (play->sceneNum == SCENE_JYASINZOU) { // Spirit Temple
        actor->level = 47;
        actor->exp = 160;
    }
}

void Leveled_Wallmaster(PlayState* play, Actor*actor) {
    actor->level = 27;
    actor->exp = 44;
    if (play->sceneNum == SCENE_HAKADANCH ||
        play->sceneNum == SCENE_HAKADAN) { // Bottom of the Well and Shadow Temple
        actor->level = 41;
        actor->exp = 129;
    } else if (play->sceneNum == SCENE_JYASINZOU) { // Spirit Temple
        actor->level = 47;
        actor->exp = 138;
    } else if (play->sceneNum == SCENE_GANONTIKA || play->sceneNum == SCENE_GANON) { // Ganon's Castle
        actor->level = 50;
        actor->exp = 150;
    }
}

void Leveled_Poh_Sisters(PlayState* play, Actor* actor) {
    actor->level = 28;
    actor->exp = 127;
}

void Leveled_LikeLike(PlayState* play, Actor* actor) {
    actor->level = 32;
    actor->exp = 99;
    if (play->sceneNum == SCENE_MIZUSIN) { // Water Temple
        actor->level = 38;
        actor->exp = 142;
    } else if (play->sceneNum == SCENE_HAKADANCH ||
               play->sceneNum == SCENE_HAKADAN) { // Bottom of the Well and Shadow Temple
        actor->level = 43;
        actor->exp = 161;
    } else if (play->sceneNum == SCENE_JYASINZOU) { // Spirit Temple
        actor->level = 48;
        actor->exp = 182;
    } else if (play->sceneNum == SCENE_GANONTIKA || play->sceneNum == SCENE_GANON) { // Ganon's Castle
        actor->level = 50;
        actor->exp = 190;
    } else    if (play->sceneNum == SCENE_MEN) {
        actor->level = 55;
        actor->exp = 260;
    }
}

void Leveled_TorchSlug(PlayState* play, Actor* actor) {
    actor->level = 33;
    actor->exp = 67;
    if (play->sceneNum == SCENE_JYASINZOU) { // Spirit Temple
        actor->level = 48;
        actor->exp = 163;
    } else if (play->sceneNum == SCENE_GANONTIKA || play->sceneNum == SCENE_GANON) { // Ganon's Castle
        actor->level = 50;
        actor->exp = 170;
    } else if (play->sceneNum == SCENE_MEN) {
        actor->level = 55;
        actor->exp = 240;
    }
}
void Leveled_Freezer(PlayState* play, Actor* actor) {
    actor->level = 35;
    actor->exp = 101;
    if (play->sceneNum == SCENE_GANONTIKA || play->sceneNum == SCENE_GANON) { // Ganon's Castle
        actor->level = 50;
        actor->exp = 160;
    }
}

void Leveled_ShellBlade(PlayState* play, Actor* actor) {
    actor->level = 38;
    actor->exp = 129;
    if (play->sceneNum == SCENE_MEN) {
        actor->level = 55;
        actor->exp = 220;
    }
}

void Leveled_RollingSpike(PlayState* play, Actor* actor) {
    actor->level = 37;
    actor->exp = 100;
    if (play->sceneNum == SCENE_MEN) {
        actor->level = 55;
        actor->exp = 200;
    }
}

void Leveled_GerudoFighter(PlayState* play, Actor* actor) {
    actor->level = 45;
    actor->exp = 455;
}

void Leveled_Leever(PlayState* play, Actor* actor) {
    actor->level = 45;
    actor->exp = 15;
}

void Leveled_Anubis(PlayState* play, Actor* actor) {
    actor->level = 48;
    if (actor->id == ACTOR_EN_ANUBICE)
        actor->exp = 120;
}


void Actor_GetLevelAndExperience(PlayState* play, Actor* actor, u16 actorIdOverride) {
    u16 actorId = actor->id;
    if (actorIdOverride != 0) {
        actorId = actorIdOverride;
    }

    switch (actorId) {
        case ACTOR_BOSS_DODONGO:
        case ACTOR_EN_DODONGO:
            Leveled_Dodongo(play, actor);
            break;
        case ACTOR_BOSS_GOMA:
        case ACTOR_EN_GOMA:
            Leveled_Gohma(play, actor);
            break;
        case ACTOR_BOSS_VA:
            Leveled_Barinade(play, actor);
            break;
        case ACTOR_BOSS_GANONDROF:
            Leveled_PhantomGanon(play, actor);
            break;
        case ACTOR_BOSS_FD:
        case ACTOR_BOSS_FD2:
            Leveled_Volvagia(play, actor);
            break;
        case ACTOR_BOSS_MO:
            Leveled_Morpha(play, actor);
            break;
        case ACTOR_BOSS_SST:
            Leveled_BongoBongo(play, actor);
            break;
        case ACTOR_BOSS_TW:
            Leveled_Twinrova(play, actor);
            break;
        case ACTOR_BOSS_GANON:
            Leveled_Ganondorf(play, actor);
            break;
        case ACTOR_BOSS_GANON2:
            Leveled_Ganon(play, actor);
            break;
        case ACTOR_EN_DEKUBABA:
            Leveled_Dekubaba(play, actor);
            break;
        case ACTOR_EN_KAREBABA:
            Leveled_StickDekuBaba(play, actor);
            break;
        case ACTOR_EN_ST:
            Leveled_Skulltula(play, actor);
            break;
        case ACTOR_EN_DEKUNUTS:
            Leveled_DekuScrub(play, actor);
            break;
        case ACTOR_EN_TITE:
            Leveled_Tektite(play, actor);
            break;
        case ACTOR_EN_CROW:
            Leveled_Guay(play, actor);
            break;
        case ACTOR_EN_OKUTA:
            Leveled_Octorock(play, actor);
            break;
        case ACTOR_EN_AM:
            Leveled_Armos(play, actor);
            break;
        case ACTOR_EN_DODOJR:
            Leveled_BabyDodongo(play, actor);
            break;
        case ACTOR_EN_FIREFLY:
            Leveled_Keese(play, actor);
            break;
        case ACTOR_EN_PEEHAT:
            Leveled_Peahat(play, actor);
            break;
        case ACTOR_EN_POH:
            Leveled_Poh(play, actor);
        case ACTOR_EN_PO_FIELD:
            Leveled_Poh_Field(play, actor);
            break;
        case ACTOR_EN_RD:
            Leveled_ReDead(play, actor);
            break;
        case ACTOR_EN_SKB:
            Leveled_Stalchild(play, actor);
            break;
        case ACTOR_EN_SW:
            Leveled_Wall_Skulltula(play, actor);
            break;
        case ACTOR_EN_VM:
            Leveled_Beamos(play, actor);
            break;
        case ACTOR_EN_WF:
            Leveled_Wolfos(play, actor);
            break;
        case ACTOR_EN_ZF:
            Leveled_Lizalfos(play, actor);
            break;
        case ACTOR_EN_BUBBLE:
            Leveled_Shabom(play, actor);
            break;
        case ACTOR_EN_BILI:
            Leveled_Biri(play, actor);
            break;
        case ACTOR_EN_VALI:
            Leveled_Bari(play, actor);
            break;
        case ACTOR_EN_TP:
            Leveled_Tailpasaran(play, actor);
            break;
        case ACTOR_EN_BA:
        case ACTOR_EN_BX:
            Leveled_JabuTentacle(play, actor);
            break;
        case ACTOR_EN_EIYER:
        case ACTOR_EN_WEIYER:
            Leveled_Stinger(play, actor);
            break;
        case ACTOR_EN_BIGOKUTA:
            Leveled_BigOctorock(play, actor);
            break;
        case ACTOR_EN_MB:
            Leveled_Moblins(play, actor);
            break;
        case ACTOR_EN_BB:
            Leveled_Bubble(play, actor);
            break;
        case ACTOR_EN_TEST:
            Leveled_Stalfos(play, actor);
            break;
        case ACTOR_EN_FLOORMAS:
            Leveled_Floormaster(play, actor);
            break;
        case ACTOR_EN_WALLMAS:
            Leveled_Wallmaster(play, actor);
            break;
        case ACTOR_EN_PO_SISTERS:
            Leveled_Poh_Sisters(play, actor);
            break;
        case ACTOR_EN_RR:
            Leveled_LikeLike(play, actor);
            break;
        case ACTOR_EN_BW:
            Leveled_TorchSlug(play, actor);
            break;
        case ACTOR_EN_FZ:
            Leveled_Freezer(play, actor);
            break;
        case ACTOR_EN_SB:
            Leveled_ShellBlade(play, actor);
            break;
        case ACTOR_EN_NY:
            Leveled_RollingSpike(play, actor);
            break;
        case ACTOR_EN_TORCH2:
            Leveled_DarkLink(play, actor);
            break;
        case ACTOR_EN_DH:
        case ACTOR_EN_DHA:
            Leveled_DeadHand(play, actor);
            break;
        case ACTOR_EN_FD:
        case ACTOR_EN_FW:
        case ACTOR_EN_FD_FIRE:
            Leveled_FlareDancer(play, actor);
            break;
        case ACTOR_EN_IK:
            Leveled_IronKnuckle(play, actor);
            break;
        case ACTOR_EN_GELDB:
            Leveled_GerudoFighter(play, actor);
            break;
        case ACTOR_EN_REEBA:
            Leveled_Leever(play, actor);
            break;
        case ACTOR_EN_ANUBICE:
        case ACTOR_EN_ANUBICE_FIRE:
            Leveled_Anubis(play, actor);
            break;
        default:
            actor->level = GET_PLAYER(play)->actor.level;
            break;
    }
}