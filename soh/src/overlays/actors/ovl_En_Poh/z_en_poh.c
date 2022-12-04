/*
 * File: z_en_poh.c
 * Overlay: ovl_En_Poh
 * Description: Graveyard Poe
 */

#include "z_en_poh.h"
#include "objects/object_poh/object_poh.h"
#include "objects/object_po_composer/object_po_composer.h"

#define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_2 | ACTOR_FLAG_4 | ACTOR_FLAG_12)

void EnPoh_Init(Actor* thisx, PlayState* play);
void EnPoh_Destroy(Actor* thisx, PlayState* play);
void EnPoh_Update(Actor* thisx, PlayState* play);

void EnPoh_UpdateLiving(Actor* thisx, PlayState* play);
void EnPoh_UpdateDead(Actor* thisx, PlayState* play);
void EnPoh_DrawRegular(Actor* thisx, PlayState* play);
void EnPoh_DrawComposer(Actor* thisx, PlayState* play);
void EnPoh_DrawSoul(Actor* thisx, PlayState* play);

void EnPoh_StaticIdle(EnPoh* this, PlayState* play);
void EnPoh_Idle(EnPoh* this, PlayState* play);
void EnPoh_ActionIdle(EnPoh* this, PlayState* play);
void EnPoh_TrickyApproach(EnPoh* this, PlayState* play);
void EnPoh_Engaging(EnPoh* this, PlayState* play);
void EnPoh_Attack(EnPoh* this, PlayState* play);
void EnPoh_RecallingFromHit(EnPoh* this, PlayState* play);
void EnPoh_FlyAway(EnPoh* this, PlayState* play);
void EnPoh_FlySideways(EnPoh* this, PlayState* play);
void EnPoh_ComposerApparate(EnPoh* this, PlayState* play);
void EnPoh_NormalApparate(EnPoh* this, PlayState* play);
void EnPoh_StartDying(EnPoh* this, PlayState* play);
void EnPoh_AttackHit(EnPoh* this, PlayState* play);
void EnPoh_TurnAround(EnPoh* this, PlayState* play);
void EnPoh_Disappear(EnPoh* this, PlayState* play);
void EnPoh_Appear(EnPoh* this, PlayState* play);
void EnPoh_Death(EnPoh* this, PlayState* play);
void EnPoh_InitiateTalk(EnPoh* this, PlayState* play);
void EnPoh_Talk(EnPoh* this, PlayState* play);
void EnPoh_EndTalk(EnPoh* this, PlayState* play);
void EnPoh_TalkRegular(EnPoh* this, PlayState* play);
void EnPoh_TalkComposer(EnPoh* this, PlayState* play);

static s16 D_80AE1A50 = 0;

const ActorInit En_Poh_InitVars = {
    ACTOR_EN_POH,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(EnPoh),
    (ActorFunc)EnPoh_Init,
    (ActorFunc)EnPoh_Destroy,
    (ActorFunc)EnPoh_Update,
    NULL,
    NULL,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT3,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    { 20, 40, 20, { 0, 0, 0 } },
};

static ColliderJntSphElementInit D_80AE1AA0[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xFFCFFFFF, 0x00, 0x08 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_ON,
        },
        { 18, { { 0, 1400, 0 }, 20 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    D_80AE1AA0,
};

static CollisionCheckInfoInit sColChkInfoInit = { 4, 25, 50, 40 };

static DamageTable sDamageTable = {
    /* Deku nut      */ DMG_ENTRY(0, 0x0),
    /* Deku stick    */ DMG_ENTRY(2, 0x0),
    /* Slingshot     */ DMG_ENTRY(1, 0x0),
    /* Explosive     */ DMG_ENTRY(2, 0x0),
    /* Boomerang     */ DMG_ENTRY(1, 0x1),
    /* Normal arrow  */ DMG_ENTRY(2, 0x0),
    /* Hammer swing  */ DMG_ENTRY(2, 0x0),
    /* Hookshot      */ DMG_ENTRY(2, 0x1),
    /* Kokiri sword  */ DMG_ENTRY(1, 0x0),
    /* Master sword  */ DMG_ENTRY(2, 0x0),
    /* Giant's Knife */ DMG_ENTRY(4, 0x0),
    /* Fire arrow    */ DMG_ENTRY(2, 0x0),
    /* Ice arrow     */ DMG_ENTRY(2, 0x0),
    /* Light arrow   */ DMG_ENTRY(2, 0x0),
    /* Unk arrow 1   */ DMG_ENTRY(2, 0x0),
    /* Unk arrow 2   */ DMG_ENTRY(2, 0x0),
    /* Unk arrow 3   */ DMG_ENTRY(2, 0x0),
    /* Fire magic    */ DMG_ENTRY(0, 0x0),
    /* Ice magic     */ DMG_ENTRY(0, 0x0),
    /* Light magic   */ DMG_ENTRY(0, 0x0),
    /* Shield        */ DMG_ENTRY(0, 0x0),
    /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
    /* Kokiri spin   */ DMG_ENTRY(1, 0x0),
    /* Giant spin    */ DMG_ENTRY(4, 0x0),
    /* Master spin   */ DMG_ENTRY(2, 0x0),
    /* Kokiri jump   */ DMG_ENTRY(2, 0x0),
    /* Giant jump    */ DMG_ENTRY(8, 0x0),
    /* Master jump   */ DMG_ENTRY(4, 0x0),
    /* Unknown 1     */ DMG_ENTRY(0, 0x0),
    /* Unblockable   */ DMG_ENTRY(0, 0x0),
    /* Hammer jump   */ DMG_ENTRY(4, 0x0),
    /* Unknown 2     */ DMG_ENTRY(0, 0x0),
};

static EnPohInfo sPoeInfo[2] = {
    {
        { 255, 170, 255 },
        { 100, 0, 150 },
        18,
        5,
        248,
        &gPoeDisappearAnim,
        &gPoeFloatAnim,
        &gPoeDamagedAnim,
        &gPoeFleeAnim,
        gPoeLanternDL,
        gPoeBurnDL,
        gPoeSoulDL,
    },
    {
        { 255, 255, 170 },
        { 0, 150, 0 },
        9,
        1,
        244,
        &gPoeComposerDisappearAnim,
        &gPoeComposerFloatAnim,
        &gPoeComposerDamagedAnim,
        &gPoeComposerFleeAnim,
        gPoeComposerLanternDL,
        gPoeComposerBurnDL,
        gPoeComposerSoulDL,
    },
};

#define MAX_OPACITY 32
#define PHASE_LENGTH 32

static Color_RGBA8 D_80AE1B4C = { 75, 20, 25, 255 };
static Color_RGBA8 D_80AE1B50 = { 80, 110, 90, 255 };
static Color_RGBA8 D_80AE1B54 = { 90, 85, 50, 255 };
static Color_RGBA8 D_80AE1B58 = { 100, 90, 100, 255 };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 3200, ICHAIN_STOP),
};

static Vec3f D_80AE1B60 = { 0.0f, 3.0f, 0.0f };
static Vec3f D_80AE1B6C = { 0.0f, 0.0f, 0.0f };

static const f32 CloseRange = 80.0f;
static const f32 ActionRange = 220.0f;
static const f32 NearEscapeRange = 300.0f;
static const f32 FarEscapeRange = 360.0f;

void EnPoh_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnItem00* collectible;
    EnPoh* this = (EnPoh*)thisx;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
    Collider_InitJntSph(play, &this->colliderSph);
    Collider_SetJntSph(play, &this->colliderSph, &this->actor, &sJntSphInit, &this->colliderSphItem);
    this->colliderSph.elements[0].dim.worldSphere.radius = 0;
    this->colliderSph.elements[0].dim.worldSphere.center.x = this->actor.world.pos.x;
    this->colliderSph.elements[0].dim.worldSphere.center.y = this->actor.world.pos.y;
    this->colliderSph.elements[0].dim.worldSphere.center.z = this->actor.world.pos.z;
    Collider_InitCylinder(play, &this->colliderCyl);
    Collider_SetCylinder(play, &this->colliderCyl, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->opacity = 0;
    this->waveTimer = PHASE_LENGTH;
    this->visibilityTimer = Rand_S16Offset(700, 300);
    this->trackingDir = 0;
    this->decisionTimer = 0;
    this->hasBeenAttacked = false;
    this->lightNode = LightContext_InsertLight(play, &play->lightCtx, &this->lightInfo);
    Lights_PointGlowSetInfo(&this->lightInfo, this->actor.home.pos.x, this->actor.home.pos.y, this->actor.home.pos.z,
                            255, 255, 255, 0);
    if (this->actor.params >= 4) {
        this->actor.params = EN_POH_NORMAL;
    }
    if (this->actor.params == EN_POH_RUPEE) {
        D_80AE1A50++;
        if (D_80AE1A50 >= 3) {
            Actor_Kill(&this->actor);
        } else {
            collectible = Item_DropCollectible(play, &this->actor.world.pos, 0x4000 | ITEM00_RUPEE_BLUE);
            if (collectible != NULL) {
                collectible->actor.speedXZ = 0.0f;
            }
        }
    } else if (this->actor.params == EN_POH_FLAT) {
        if (Flags_GetSwitch(play, 0x28) || Flags_GetSwitch(play, 0x9)) {
            Actor_Kill(&this->actor);
        } else {
            Flags_SetSwitch(play, 0x28);
        }
    } else if (this->actor.params == EN_POH_SHARP) {
        if (Flags_GetSwitch(play, 0x29) || Flags_GetSwitch(play, 0x9)) {
            Actor_Kill(&this->actor);
        } else {
            Flags_SetSwitch(play, 0x29);
        }
    }
    if (this->actor.params < EN_POH_SHARP) {
        this->objectIdx = Object_GetIndex(&play->objectCtx, OBJECT_POH);
        this->infoIdx = EN_POH_INFO_NORMAL;
        this->actor.naviEnemyId = 0x44;
    } else {
        this->objectIdx = Object_GetIndex(&play->objectCtx, OBJECT_PO_COMPOSER);
        this->infoIdx = EN_POH_INFO_COMPOSER;
        this->actor.naviEnemyId = 0x43;
    }
    this->info = &sPoeInfo[this->infoIdx];
    if (this->objectIdx < 0) {
        Actor_Kill(&this->actor);
    }
}

void EnPoh_Destroy(Actor* thisx, PlayState* play) {
    EnPoh* this = (EnPoh*)thisx;

    LightContext_RemoveLight(play, &play->lightCtx, this->lightNode);
    Collider_DestroyJntSph(play, &this->colliderSph);
    Collider_DestroyCylinder(play, &this->colliderCyl);
    if (this->actor.params == EN_POH_RUPEE) {
        D_80AE1A50--;
    }
}

void EnPoh_SetupStaticIdle(EnPoh* this) {
    Animation_PlayLoop(&this->skelAnime, this->info->idleAnim);
    this->actionTimer = Rand_S16Offset(2, 3);
    this->actionFunc = EnPoh_StaticIdle;
    this->actor.speedXZ = 0.0f;
}

void EnPoh_SetupIdle(EnPoh* this) {
    Animation_PlayLoop(&this->skelAnime, this->info->idleAnim2);
    this->actionTimer = Rand_S16Offset(5, 3);//original:12,change:5
    this->actionFunc = EnPoh_Idle;
}

void EnPoh_SetupActionIdle(EnPoh* this) {
    Animation_PlayLoop(&this->skelAnime, this->info->idleAnim2);
    this->actionFunc = EnPoh_ActionIdle;
    this->actionTimer = 0;
    this->actor.speedXZ = 2.0f;
}

void EnPoh_SetupTrickyApproach(EnPoh* this) {
    Animation_PlayLoop(&this->skelAnime, this->info->idleAnim2);
    this->actionFunc = EnPoh_TrickyApproach;
    this->actionTimer = 200;
    this->waveTimer = 0;
    this->actor.speedXZ = 4.0f;
    this->decisionTimer = 3;
    this->trackingDir = Rand_S16Offset(-1,3); //(Rand_ZeroOne() < 0.5) ? 1 : 0;
}

void EnPoh_SetupEngaging(EnPoh* this) {
    Animation_PlayLoop(&this->skelAnime, this->info->idleAnim);
    this->actionFunc = EnPoh_Engaging;
    this->actionTimer = 200;
    this->decisionTimer = 3;
}

void EnPoh_SetupAttack(EnPoh* this) {
    if (this->infoIdx == EN_POH_INFO_NORMAL) {
        Animation_MorphToLoop(&this->skelAnime, &gPoeAttackAnim, -6.0f);
    } else {
        Animation_PlayLoop(&this->skelAnime, &gPoeComposerAttackAnim);
    }
    this->actionTimer = 12;
    this->actor.speedXZ = 0.0f;
    if (this->actor.params >= EN_POH_SHARP)
        this->skelAnime.playSpeed = 5.0f;
    else
        this->skelAnime.playSpeed = 3.0f;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_LAUGH);
    this->actionFunc = EnPoh_Attack;
}

void EnPoh_SetupRecallingFromHit(EnPoh* this) {
    this->hasBeenAttacked = true;
    if (this->infoIdx == EN_POH_INFO_NORMAL) {
        Animation_MorphToPlayOnce(&this->skelAnime, &gPoeDamagedAnim, -6.0f);
    } else {
        Animation_PlayOnce(&this->skelAnime, &gPoeComposerDamagedAnim);
    }
    if (this->colliderCyl.info.acHitInfo->toucher.dmgFlags & 0x0001F824) {
        this->actor.world.rot.y = this->colliderCyl.base.ac->world.rot.y;
    } else {
        this->actor.world.rot.y = Actor_WorldYawTowardActor(&this->actor, this->colliderCyl.base.ac) + 0x8000;
    }
    this->colliderCyl.base.acFlags &= ~AC_ON;
    this->actor.speedXZ = 6.0f;
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 0x10);
    this->actionFunc = EnPoh_RecallingFromHit;
}

void EnPoh_SetupFlyAway(EnPoh* this) {
    Animation_MorphToLoop(&this->skelAnime, this->info->fleeAnim, -5.0f);
    this->actor.speedXZ = 5.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y + 0x8000;
    this->colliderCyl.base.acFlags |= AC_ON;
    this->actionTimer = 100;
    this->actionFunc = EnPoh_FlyAway;
}

void EnPoh_SetupFlySideways(EnPoh* this) {
    Animation_MorphToLoop(&this->skelAnime, this->info->fleeAnim, -5.0f);
    if (this->actor.params >= EN_POH_SHARP)
        this->actor.speedXZ = 9.0f;
    else
        this->actor.speedXZ = 5.5f;
    this->trackingDir = (Rand_ZeroOne() < 0.5f ? 1 : -1);
    this->actor.world.rot.y = this->actor.shape.rot.y + 0x4000*this->trackingDir;
    this->colliderCyl.base.acFlags |= AC_ON;
    if (this->actor.xzDistToPlayer > ActionRange)
        this->actionTimer = Rand_S16Offset(10, 21);
    else
        this->actionTimer = Rand_S16Offset(5, 8);
    this->actionFunc = EnPoh_FlySideways;
}

void EnPoh_SetupInitialAction(EnPoh* this) {
    this->lightColor.a = 0;
    this->actor.flags &= ~ACTOR_FLAG_0;
    if (this->infoIdx == EN_POH_INFO_NORMAL) {
        Animation_PlayOnceSetSpeed(&this->skelAnime, &gPoeAppearAnim, 0.0f);
        this->actionFunc = EnPoh_NormalApparate;
    } else {
        Animation_PlayOnceSetSpeed(&this->skelAnime, &gPoeComposerAppearAnim, 1.0f);
        this->actor.world.pos.y = this->actor.home.pos.y + 20.0f;
        this->actor.colChkInfo.health = 8;
        this->colliderSph.elements[0].info.toucher.damage = 0x10;
        this->hasBeenAttacked = true;
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_LAUGH);
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_APPEAR);
        this->actionFunc = EnPoh_ComposerApparate;
    }
}

void EnPoh_SetupStartDying(EnPoh* this) {
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionTimer = 0;
    this->actor.naviEnemyId = 0xFF;
    this->actor.flags &= ~ACTOR_FLAG_0;
    this->actionFunc = EnPoh_StartDying;
}

void EnPoh_SetupAttackHit(EnPoh* this) {
    Animation_PlayOnce(&this->skelAnime, this->info->idleAnim2);
    this->actionFunc = EnPoh_AttackHit;
    this->actor.speedXZ = -5.0f;
}

void EnPoh_SetupTurnAround(EnPoh* this) {
    Animation_PlayLoop(&this->skelAnime, this->info->idleAnim);
    this->yRotAim = this->actor.world.rot.y + 0x8000;
    this->actionFunc = EnPoh_TurnAround;
    this->actor.speedXZ = 0.0f;
}

void EnPoh_SetupDisappear(EnPoh* this) {
    this->opacity = MAX_OPACITY;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_DISAPPEAR);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_LAUGH);
    this->actionFunc = EnPoh_Disappear;
}

void EnPoh_SetupAppear(EnPoh* this) {
    this->opacity = 0;
    this->actor.speedXZ = 0.0f;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_APPEAR);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_LAUGH);
    this->actionFunc = EnPoh_Appear;
}

void EnPoh_SetupDeath(EnPoh* this, PlayState* play) {
    this->actor.update = EnPoh_UpdateDead;
    this->actor.draw = EnPoh_DrawSoul;
    this->actor.shape.shadowDraw = NULL;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.flags |= ACTOR_FLAG_4;
    this->actor.gravity = -1.0f;
    this->actor.shape.yOffset = 1500.0f;
    this->actor.world.pos.y -= 15.0f;
    if (this->infoIdx != EN_POH_INFO_COMPOSER) {
        this->actor.shape.rot.x = -0x8000;
    }
    Actor_ChangeCategory(play, &play->actorCtx, &this->actor, 8);
    this->actionTimer = 60;
    this->actionFunc = EnPoh_Death;
}

void func_80ADE6D4(EnPoh* this) {
    Lights_PointNoGlowSetInfo(&this->lightInfo, this->actor.world.pos.x, this->actor.world.pos.y,
                              this->actor.world.pos.z, 0, 0, 0, 0);
    this->visibilityTimer = 0;
    this->actor.shape.rot.y = 0;
    this->lightColor.r = 0;
    this->lightColor.a = 0;
    this->actor.shape.yOffset = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    if (this->actor.params >= EN_POH_SHARP) {
        this->lightColor.g = 200;
        this->lightColor.b = 0;
    } else {
        this->lightColor.g = 0;
        this->lightColor.b = 200;
    }
    this->actor.scale.x = 0.0f;
    this->actor.scale.y = 0.0f;
    this->actor.shape.rot.x = 0;
    this->actor.home.pos.y = this->actor.world.pos.y;
    Audio_PlayActorSound2(&this->actor, NA_SE_EV_METAL_BOX_BOUND);
    this->actionFunc = EnPoh_InitiateTalk;
}

void EnPoh_SetupTalk(EnPoh* this, PlayState* play) {
    this->actor.home.pos.y = this->actor.world.pos.y;
    Actor_SetFocus(&this->actor, -10.0f);
    this->colliderCyl.dim.radius = 13;
    this->colliderCyl.dim.height = 30;
    this->colliderCyl.dim.yShift = 0;
    this->colliderCyl.dim.pos.x = this->actor.world.pos.x;
    this->colliderCyl.dim.pos.y = this->actor.world.pos.y - 20.0f;
    this->colliderCyl.dim.pos.z = this->actor.world.pos.z;
    this->colliderCyl.base.ocFlags1 = OC1_ON | OC1_TYPE_PLAYER;
    if (this->actor.params == EN_POH_FLAT || this->actor.params == EN_POH_SHARP) {
        if (CHECK_QUEST_ITEM(QUEST_SONG_SUN)) {
            this->actor.textId = 0x5000;
        } else if (!Flags_GetSwitch(play, 0xA) && !Flags_GetSwitch(play, 0xB)) {
            this->actor.textId = 0x500F;
        } else if ((this->actor.params == EN_POH_FLAT && Flags_GetSwitch(play, 0xA)) ||
                   (this->actor.params == EN_POH_SHARP && Flags_GetSwitch(play, 0xB))) {
            this->actor.textId = 0x5013;
        } else {
            this->actor.textId = 0x5012;
        }
    } else {
        this->actor.textId = 0x5005;
    }
    this->actionTimer = 200;
    this->waveTimer = PHASE_LENGTH;
    this->actor.flags |= ACTOR_FLAG_0;
    this->actionFunc = EnPoh_Talk;
}

void EnPoh_SetupEndTalk(EnPoh* this, s32 arg1) {
    if (arg1) {
        Audio_StopSfxByPosAndId(&this->actor.projectedPos, NA_SE_EN_PO_BIG_CRY - SFX_FLAG);
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_LAUGH);
    }
    this->actionFunc = EnPoh_EndTalk;
}

void EnPoh_SetupTalkRegular(EnPoh* this) {
    this->actionFunc = EnPoh_TalkRegular;
    this->actor.home.pos.y = this->actor.world.pos.y - 15.0f;
}

void EnPoh_SetupTalkComposer(EnPoh* this) {
    this->actionFunc = EnPoh_TalkComposer;
}

void EnPoh_MoveTowardsPlayerHeight(EnPoh* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    Math_StepToF(&this->actor.world.pos.y, player->actor.world.pos.y, 1.0f);
    this->actor.world.pos.y += 2.5f * Math_SinS(this->waveTimer * 0x800);
    if (this->waveTimer != 0) {
        this->waveTimer -= 1;
    }
    if (this->waveTimer == 0) {
        this->waveTimer = PHASE_LENGTH;
    }
}

void EnPoh_MoveAroundPlayerHeight(EnPoh* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    f32 phasePoint = player->actor.world.pos.y + 30.0f * (1 -Math_CosS(this->waveTimer * 0x800));

    Math_StepToF(&this->actor.world.pos.y, phasePoint, 3.5f);
    //this->actor.world.pos.y += /*(MIN(1.0,(MAX(ActionRange, this->actor.xzDistToPlayer)-ActionRange)/ActionRange))**/7.0f * Math_SinS(this->waveTimer * 0x400);
    if (this->waveTimer != 0) {
        this->waveTimer -= 1;
    }
    if (this->waveTimer == 0) {
        this->waveTimer = PHASE_LENGTH;
    }
}

s8 EnPoh_MoveAtPlayerHeight(EnPoh* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    f32 phasePoint = player->actor.world.pos.y + 4.0f * (1 -Math_CosS(this->waveTimer * 0x800));

    s8 result = Math_StepToF(&this->actor.world.pos.y, phasePoint, 5.0f);
    //this->actor.world.pos.y += /*(MIN(1.0,(MAX(ActionRange, this->actor.xzDistToPlayer)-ActionRange)/ActionRange))**/7.0f * Math_SinS(this->waveTimer * 0x400);
    if (this->waveTimer != 0) {
        this->waveTimer -= 1;
    }
    if (this->waveTimer == 0) {
        this->waveTimer = PHASE_LENGTH;
    }

    return result;
}

void EnPo_TurnToHome(EnPoh* this) {
    if (Actor_WorldDistXZToPoint(&this->actor, &this->actor.home.pos) > 400.0f) {
        this->yRotAim = Actor_WorldYawTowardPoint(&this->actor, &this->actor.home.pos);
    }
    Math_ScaledStepToS(&this->actor.world.rot.y, this->yRotAim, 0x71C);
}

void EnPoh_StaticIdle(EnPoh* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 0.0f) && this->actionTimer != 0) {
        this->actionTimer--;
    }
    EnPoh_MoveTowardsPlayerHeight(this, play);
    if (this->actor.xzDistToPlayer < ActionRange) {
        EnPoh_SetupActionIdle(this);
    } else if (this->actionTimer == 0) {
        EnPoh_SetupIdle(this);
    }
    if (this->lightColor.a == 255) {
        func_8002F974(&this->actor, NA_SE_EN_PO_FLY - SFX_FLAG);
    }
}

void EnPoh_Idle(EnPoh* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Math_StepToF(&this->actor.speedXZ, 1.0f, 0.2f);
    if (Animation_OnFrame(&this->skelAnime, 0.0f) && this->actionTimer != 0) {
        this->actionTimer--;
    }
    EnPo_TurnToHome(this);
    EnPoh_MoveTowardsPlayerHeight(this, play);
    if (this->actor.xzDistToPlayer < ActionRange && this->actionTimer < 19) {
        EnPoh_SetupActionIdle(this);
    } else if (this->actionTimer == 0) {
        if (Rand_ZeroOne() < 0.1f) {
            EnPoh_SetupTurnAround(this);
        } else {
            EnPoh_SetupStaticIdle(this);
        }
    }
    if (this->lightColor.a == 255) {
        func_8002F974(&this->actor, NA_SE_EN_PO_FLY - SFX_FLAG);
    }
}

void EnPoh_ActionIdle(EnPoh* this, PlayState* play) {
    Player* player;
    s16 facingDiff;

    player = GET_PLAYER(play);
    SkelAnime_Update(&this->skelAnime);
    if (this->actionTimer != 0) {
        this->actionTimer--;
    }
    facingDiff = this->actor.yawTowardsPlayer - player->actor.shape.rot.y;
    if (facingDiff >= 0x3001) {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer + 0x3000, 0x71C);
    } else if (facingDiff < -0x3000) {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer - 0x3000, 0x71C);
    } else {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0x71C);
    }
    EnPoh_MoveTowardsPlayerHeight(this, play);
    if (this->actor.xzDistToPlayer > 280.0f) {
        EnPoh_SetupIdle(this);
    } else if (this->actionTimer == 0 && this->actor.xzDistToPlayer < 140.0f &&
               !Player_IsFacingActor(&this->actor, 0x2AAA, play)) {
        EnPoh_SetupAttack(this);
    }
    if (this->lightColor.a == 255) {
        func_8002F974(&this->actor, NA_SE_EN_PO_FLY - SFX_FLAG);
    }
}

void EnPoh_TrickyApproach(EnPoh* this, PlayState* play) {
    Player* player;

    player = GET_PLAYER(play);
    SkelAnime_Update(&this->skelAnime);
    if (this->actionTimer != 0) {
        this->actionTimer--;
    }
    this->actor.speedXZ = 5.0f;

    if (this->decisionTimer > 0)
        this->decisionTimer--;
    else if (Rand_ZeroOne() < 0.1) {
        this->trackingDir = Rand_S16Offset(-1,3); //(Rand_ZeroOne() < 0.5) ? 1 : 0;
        this->decisionTimer = 3;
    }

    if (this->trackingDir > 0) {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer + 0x3000, 0x1000);
    } else if (this->trackingDir < 0) {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer - 0x3000, 0x1000);
    } else {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0x1000);
    }
    EnPoh_MoveAroundPlayerHeight(this, play);
    if (this->actionTimer == 0) {
        EnPoh_SetupIdle(this);
    } else if (this->actor.xzDistToPlayer < ActionRange) {
        if (this->actionTimer == 0 && this->actor.xzDistToPlayer < 140.0f &&
                !Player_IsFacingActor(&this->actor, 0x2AAA, play)) {
            EnPoh_SetupAttack(this);
        } else {
            EnPoh_SetupEngaging(this);
        }
    }
    if (this->lightColor.a == 255) {
        func_8002F974(&this->actor, NA_SE_EN_PO_FLY - SFX_FLAG);
    }
}

void EnPoh_Engaging(EnPoh* this, PlayState* play) {
    Player* player;

    player = GET_PLAYER(play);
    SkelAnime_Update(&this->skelAnime);
    if (this->actionTimer != 0) {
        this->actionTimer--;
    }

    if (this->decisionTimer > 0)
        this->decisionTimer--;
    else if (Rand_ZeroOne() < 0.2) {
        this->actor.speedXZ = (Rand_ZeroOne()-0.5)*12;
        this->decisionTimer = Rand_S16Offset(3,3);
    }

    if (this->actor.xzDistToPlayer < CloseRange)
        this->actor.speedXZ = -ABS(this->actor.speedXZ);

    Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0x1800);

    s8 atTargetHeight = EnPoh_MoveAtPlayerHeight(this, play);
    if (this->actionTimer == 0 && this->lightColor.a == 255) {
        EnPoh_SetupDisappear(this);
    } else if (this->actor.xzDistToPlayer < ActionRange) {
        if (isPlayerInSpinAttack(play) || (Player_IsFacingActor(&this->actor, 0x2000, play) && this->actor.xzDistToPlayer < 120.0f &&
                                            (isPlayerInBasicHorizontalSlash(play) || (player->swordAnimation == PLAYER_MWA_HAMMER_SIDE && player->swordState)))) {
            this->actor.speedXZ = -6.5;
            this->decisionTimer += 3;
        } else if (Player_IsFacingActor(&this->actor, 0x800, play) && (player->swordState != 0 || isProjectileNotched(play))) {
            EnPoh_SetupFlySideways(this);
        } else if ((this->actor.xzDistToPlayer > CloseRange || this->actor.xzDistToPlayer < 35.0f) &&
                (Rand_ZeroOne() < 0.15)) {
            EnPoh_SetupAttack(this);
        } else {
            if (Rand_ZeroOne() < 0.15)
                EnPoh_SetupFlySideways(this);
        }
    } else {
        EnPoh_SetupTrickyApproach(this);
    }
    if (this->lightColor.a == 255) {
        func_8002F974(&this->actor, NA_SE_EN_PO_FLY - SFX_FLAG);
    }
}

void EnPoh_Attack(EnPoh* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_KANTERA);
        if (this->actionTimer != 0) {
            this->actionTimer--;
        }
    }
    EnPoh_MoveTowardsPlayerHeight(this, play);
    if (this->actionTimer >= 10) {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0x1000);
    } else if (this->actionTimer > 0) {
        if (this->actor.params >= EN_POH_SHARP)
            this->actor.speedXZ = 9.0f;
        else
            this->actor.speedXZ = 6.5f;
        this->skelAnime.playSpeed = 2.0f;
        if (Actor_IsFacingPlayer(this, 0x2000))
            Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0x150);
    } else if (this->actionTimer == 0) {
        if (Rand_ZeroOne() < 0.3)
            EnPoh_SetupDisappear(this);
        else
            EnPoh_SetupTrickyApproach(this);
        this->actionTimer = 23;
    }
}

void EnPoh_RecallingFromHit(EnPoh* this, PlayState* play) {
    Math_StepToF(&this->actor.speedXZ, 8.0f, 0.5f);
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->actor.colChkInfo.health != 0) {
            EnPoh_SetupFlyAway(this);
        } else {
            EnPoh_SetupStartDying(this);
        }
    }
}

void EnPoh_NormalApparate(EnPoh* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        this->lightColor.a = 255;
        this->visibilityTimer = Rand_S16Offset(700, 300);
        this->actor.flags |= ACTOR_FLAG_0;
        EnPoh_SetupIdle(this);
    } else if (this->skelAnime.curFrame > 10.0f) {
        this->lightColor.a = ((this->skelAnime.curFrame - 10.0f) * 0.05f) * 255.0f;
    }
    if (this->skelAnime.playSpeed < 0.5f && this->actor.xzDistToPlayer < 280.0f) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_APPEAR);
        this->skelAnime.playSpeed = 1.0f;
    }
}

void EnPoh_ComposerApparate(EnPoh* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        this->lightColor.a = 255;
        this->visibilityTimer = Rand_S16Offset(700, 300);
        this->actor.flags |= ACTOR_FLAG_0;
        EnPoh_SetupIdle(this);
    } else {
        this->lightColor.a = CLAMP_MAX((s32)(this->skelAnime.curFrame * 25.5f), 255);
    }
}

void EnPoh_StartDying(EnPoh* this, PlayState* play) {
    Vec3f vec;
    f32 multiplier;
    f32 newScale;
    s32 pad;
    s32 pad1;

    this->actionTimer++;
    if (this->actionTimer < 8) {
        if (this->actionTimer < 5) {
            vec.y = Math_SinS((this->actionTimer * 0x1000) - 0x4000) * 23.0f + (this->actor.world.pos.y + 40.0f);
            multiplier = Math_CosS((this->actionTimer * 0x1000) - 0x4000) * 23.0f;
            vec.x = Math_SinS(Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) + 0x4800) * multiplier +
                    this->actor.world.pos.x;
            vec.z = Math_CosS(Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) + 0x4800) * multiplier +
                    this->actor.world.pos.z;
        } else {
            vec.y = (this->actor.world.pos.y + 40.0f) + (15.0f * (this->actionTimer - 5));
            vec.x =
                Math_SinS(Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) + 0x4800) * 23.0f + this->actor.world.pos.x;
            vec.z =
                Math_CosS(Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) + 0x4800) * 23.0f + this->actor.world.pos.z;
        }
        EffectSsDeadDb_Spawn(play, &vec, &D_80AE1B60, &D_80AE1B6C, this->actionTimer * 10 + 80, 0, 255, 255, 255, 255,
                             0, 0, 255, 1, 9, 1);
        vec.x = (this->actor.world.pos.x + this->actor.world.pos.x) - vec.x;
        vec.z = (this->actor.world.pos.z + this->actor.world.pos.z) - vec.z;
        EffectSsDeadDb_Spawn(play, &vec, &D_80AE1B60, &D_80AE1B6C, this->actionTimer * 10 + 80, 0, 255, 255, 255, 255,
                             0, 0, 255, 1, 9, 1);
        vec.x = this->actor.world.pos.x;
        vec.z = this->actor.world.pos.z;
        EffectSsDeadDb_Spawn(play, &vec, &D_80AE1B60, &D_80AE1B6C, this->actionTimer * 10 + 80, 0, 255, 255, 255, 255,
                             0, 0, 255, 1, 9, 1);
        if (this->actionTimer == 1) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_EXTINCT);
        }
    } else if (this->actionTimer == 28) {
        EnPoh_SetupDeath(this, play);
    } else if (this->actionTimer >= 19) {
        newScale = (28 - this->actionTimer) * 0.001f;
        this->actor.world.pos.y += 5.0f;
        this->actor.scale.z = newScale;
        this->actor.scale.y = newScale;
        this->actor.scale.x = newScale;
    }
    if (this->actionTimer == 18) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_DEAD2);
    }
}

void EnPoh_AttackHit(EnPoh* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (this->hasBeenAttacked)
            EnPoh_SetupTrickyApproach(this);
        else
            EnPoh_SetupIdle(this);
        this->actionTimer = 23;
    } else {
        Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
        this->actor.shape.rot.y += 0x1000;
    }
}

void EnPoh_TurnAround(EnPoh* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (Math_ScaledStepToS(&this->actor.world.rot.y, this->yRotAim, 1820) != 0) {
        EnPoh_SetupIdle(this);
    }
    if (this->actor.xzDistToPlayer < ActionRange) {
        EnPoh_SetupActionIdle(this);
    }
    EnPoh_MoveTowardsPlayerHeight(this, play);
}

void EnPoh_Disappear(EnPoh* this, PlayState* play) {
    if (this->opacity != 0) {
        this->opacity--;
    }
    this->actor.world.rot.y += 0x1000;
    EnPoh_MoveTowardsPlayerHeight(this, play);
    this->lightColor.a = this->opacity * 7.96875f;
    if (this->opacity == 0) {
        this->visibilityTimer = Rand_S16Offset(100, 50);
        EnPoh_SetupIdle(this);
    }
}

void EnPoh_Appear(EnPoh* this, PlayState* play) {
    this->opacity += 2;
    if (this->opacity > MAX_OPACITY)
        this->opacity = MAX_OPACITY;
    this->actor.world.rot.y -= 0x2000;
    EnPoh_MoveTowardsPlayerHeight(this, play);
    this->lightColor.a = this->opacity * 7.96875f;
    if (this->opacity >= MAX_OPACITY) {
        this->visibilityTimer = Rand_S16Offset(700, 300);
        this->opacity = 0;
        if (this->hasBeenAttacked)
            EnPoh_SetupTrickyApproach(this);
        else
            EnPoh_SetupIdle(this);
    }
}

void EnPoh_FlyAway(EnPoh* this, PlayState* play) {
    f32 multiplier;
    if (this->actionTimer > 0) {
        this->actionTimer--;
    }

    SkelAnime_Update(&this->skelAnime);
    multiplier = Math_SinS(this->waveTimer * 0x800) * 3.0f;
    this->actor.world.pos.x -= multiplier * Math_CosS(this->actor.shape.rot.y);
    this->actor.world.pos.z += multiplier * Math_SinS(this->actor.shape.rot.y);
    Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer + 0x8000, 0x71C);
    EnPoh_MoveTowardsPlayerHeight(this, play);
    if (this->actionTimer == 0 || (this->lightColor.a > 240 && this->actor.xzDistToPlayer > NearEscapeRange) || this->actor.xzDistToPlayer > FarEscapeRange) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (this->actor.xzDistToPlayer < 100.0f || isProjectileNotched(play))
            EnPoh_SetupFlySideways(this);
        else if (this->lightColor.a < 10) {
            EnPoh_SetupIdle(this);
        }
        else {
            EnPoh_SetupTrickyApproach(this);
        }
    }
    func_8002F974(&this->actor, NA_SE_EN_PO_AWAY - SFX_FLAG);
}

void EnPoh_FlySideways(EnPoh* this, PlayState* play) {
    f32 multiplier;
    if (this->actionTimer > 0) {
        this->actionTimer--;
    }

    SkelAnime_Update(&this->skelAnime);
    multiplier = Math_SinS(this->waveTimer * 0x800) * 3.0f;
    this->actor.world.pos.x -= multiplier * Math_CosS(this->actor.shape.rot.y);
    this->actor.world.pos.z += multiplier * Math_SinS(this->actor.shape.rot.y);
    Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer + 0x4000*this->trackingDir, 0x71C);
    EnPoh_MoveTowardsPlayerHeight(this, play);
    if (this->actionTimer == 0) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (this->lightColor.a < 10) {
            EnPoh_SetupIdle(this);
        }
        else {
            EnPoh_SetupTrickyApproach(this);
        }
    }
    func_8002F974(&this->actor, NA_SE_EN_PO_AWAY - SFX_FLAG);
}

void EnPoh_Death(EnPoh* this, PlayState* play) {
    s32 objId;

    if (this->actionTimer != 0) {
        this->actionTimer--;
    }
    if (this->actor.bgCheckFlags & 1) {
        objId = (this->infoIdx == EN_POH_INFO_COMPOSER) ? OBJECT_PO_COMPOSER : OBJECT_POH;
        EffectSsHahen_SpawnBurst(play, &this->actor.world.pos, 6.0f, 0, 1, 1, 15, objId, 10,
                                 this->info->lanternDisplayList);
        func_80ADE6D4(this);
    } else if (this->actionTimer == 0) {
        Actor_Kill(&this->actor);
        return;
    }
    Actor_MoveForward(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 10.0f, 10.0f, 4);
}

void func_80ADFA90(EnPoh* this, s32 arg1) {
    f32 multiplier;

    this->lightColor.a = CLAMP(this->lightColor.a + arg1, 0, 255);
    if (arg1 < 0) {
        multiplier = this->lightColor.a * (1.0f / 255);
        this->actor.scale.x = this->actor.scale.z = 0.0056000002f * multiplier + 0.0014000001f;
        this->actor.scale.y = (0.007f - 0.007f * multiplier) + 0.007f;
    } else {
        multiplier = 1.0f;
        this->actor.scale.x = this->actor.scale.y = this->actor.scale.z = this->lightColor.a * (0.007f / 0xFF);
        this->actor.world.pos.y = this->actor.home.pos.y + (1.0f / 17.0f) * this->lightColor.a;
    }
    this->lightColor.r = this->info->lightColor.r * multiplier;
    this->lightColor.g = this->info->lightColor.g * multiplier;
    this->lightColor.b = this->info->lightColor.b * multiplier;
    Lights_PointNoGlowSetInfo(&this->lightInfo, this->actor.world.pos.x, this->actor.world.pos.y,
                              this->actor.world.pos.z, this->info->lightColor.r, this->info->lightColor.g,
                              this->info->lightColor.b, this->lightColor.a * (200.0f / 255));
}

void EnPoh_InitiateTalk(EnPoh* this, PlayState* play) {
    this->actor.home.pos.y += 2.0f;
    func_80ADFA90(this, 20);
    if (this->lightColor.a == 255) {
        EnPoh_SetupTalk(this, play);
    }
}

void EnPoh_Talk(EnPoh* this, PlayState* play) {
    if (this->actionTimer != 0) {
        this->actionTimer--;
    }
    if (Actor_ProcessTalkRequest(&this->actor, play)) {
        if (this->actor.params >= EN_POH_SHARP) {
            EnPoh_SetupTalkComposer(this);
        } else {
            EnPoh_SetupTalkRegular(this);
        }
        return;
    }
    if (this->actionTimer == 0) {
        EnPoh_SetupEndTalk(this, 1);
        this->actor.flags &= ~ACTOR_FLAG_16;
        return;
    }
    if (this->colliderCyl.base.ocFlags1 & OC1_HIT) {
        this->actor.flags |= ACTOR_FLAG_16;
        func_8002F2F4(&this->actor, play);
    } else {
        this->actor.flags &= ~ACTOR_FLAG_16;
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderCyl.base);
    }
    this->actor.world.pos.y = Math_SinS(this->waveTimer * 0x800) * 5.0f + this->actor.home.pos.y;
    if (this->waveTimer != 0) {
        this->waveTimer -= 1;
    }
    if (this->waveTimer == 0) {
        this->waveTimer = PHASE_LENGTH;
    }
    this->colliderCyl.dim.pos.y = this->actor.world.pos.y - 20.0f;
    Actor_SetFocus(&this->actor, -10.0f);
    Lights_PointNoGlowSetInfo(&this->lightInfo, this->actor.world.pos.x, this->actor.world.pos.y,
                              this->actor.world.pos.z, this->info->lightColor.r, this->info->lightColor.g,
                              this->info->lightColor.b, this->lightColor.a * (200.0f / 255));
}

void EnPoh_EndTalk(EnPoh* this, PlayState* play) {
    func_80ADFA90(this, -13);
    if (this->lightColor.a == 0) {
        Actor_Kill(&this->actor);
    }
}

void EnPoh_TalkRegular(EnPoh* this, PlayState* play) {
    if (this->actor.textId != 0x5005) {
        func_80ADFA90(this, -13);
    } else {
        func_8002F974(&this->actor, NA_SE_EN_PO_BIG_CRY - SFX_FLAG);
    }
    if (Message_GetState(&play->msgCtx) == TEXT_STATE_CHOICE) {
        if (Message_ShouldAdvance(play)) {
            Audio_StopSfxByPosAndId(&this->actor.projectedPos, NA_SE_EN_PO_BIG_CRY - SFX_FLAG);
            if (play->msgCtx.choiceIndex == 0) {
                if (Inventory_HasEmptyBottle()) {
                    this->actor.textId = 0x5008;
                    Item_Give(play, ITEM_POE);
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_BIG_GET);
                } else {
                    this->actor.textId = 0x5006;
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_LAUGH);
                }
            } else {
                this->actor.textId = 0x5007;
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_LAUGH);
            }
            Message_ContinueTextbox(play, this->actor.textId);
        }
    } else if (Actor_TextboxIsClosing(&this->actor, play)) {
        EnPoh_SetupEndTalk(this, 0);
    }
}

void EnPoh_TalkComposer(EnPoh* this, PlayState* play) {
    func_8002F974(&this->actor, NA_SE_EN_PO_BIG_CRY - SFX_FLAG);
    if (Message_GetState(&play->msgCtx) == TEXT_STATE_CHOICE) {
        if (Message_ShouldAdvance(play)) {
            if (play->msgCtx.choiceIndex == 0) {
                if (!Flags_GetSwitch(play, 0xB) && !Flags_GetSwitch(play, 0xA)) {
                    this->actor.textId = 0x5010;
                } else {
                    this->actor.textId = 0x5014;
                }
                Message_ContinueTextbox(play, this->actor.textId);
            } else {
                if (this->actor.params == EN_POH_SHARP) {
                    Flags_SetSwitch(play, 0xB);
                } else {
                    Flags_SetSwitch(play, 0xA);
                }
                EnPoh_SetupEndTalk(this, 1);
            }
        }
    } else if (Actor_TextboxIsClosing(&this->actor, play)) {
        if (this->actor.textId == 0x5000) {
            Flags_SetSwitch(play, 9);
        }
        EnPoh_SetupEndTalk(this, 1);
    }
}

void EnPo_CollisionCheck(EnPoh* this, PlayState* play) {
    if (this->colliderCyl.base.acFlags & AC_HIT) {
        this->colliderCyl.base.acFlags &= ~AC_HIT;
        if (this->actor.colChkInfo.damageEffect != 0 || this->actor.colChkInfo.damage != 0) {
            if (Actor_ApplyDamage(&this->actor) == 0) {
                Enemy_StartFinishingBlow(play, &this->actor);
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_DEAD);
            } else {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_DAMAGE);
            }
            EnPoh_SetupRecallingFromHit(this);
        }
    }
}

void EnPoh_UpdateVisibility(EnPoh* this) {
    if (this->actionFunc != EnPoh_Appear && this->actionFunc != EnPoh_Disappear && this->actionFunc != EnPoh_NormalApparate &&
        this->actionFunc != EnPoh_ComposerApparate) {
        if (this->visibilityTimer != 0) {
            this->visibilityTimer--;
        }
        if (this->lightColor.a == 255) {
            if (this->actor.isTargeted) {
                this->opacity++;
                this->opacity = CLAMP_MAX(this->opacity, 20);
            } else {
                this->opacity = 0;
            }
            if ((this->opacity == 20 || this->visibilityTimer == 0) &&
                (this->actionFunc == EnPoh_StaticIdle || this->actionFunc == EnPoh_Idle ||
                 this->actionFunc == EnPoh_ActionIdle || this->actionFunc == EnPoh_FlyAway ||
                 this->actionFunc == EnPoh_TurnAround || this->actionFunc ==  EnPoh_FlySideways ||
                 this->actionFunc == EnPoh_TrickyApproach || this->actionFunc == EnPoh_Engaging)) {
                EnPoh_SetupDisappear(this);
            }
        } else if (this->lightColor.a == 0 && this->visibilityTimer == 0 && !this->actor.isTargeted &&
                   (this->actionFunc == EnPoh_StaticIdle || this->actionFunc == EnPoh_Idle ||
                    this->actionFunc == EnPoh_ActionIdle || this->actionFunc == EnPoh_TurnAround ||
                    this->actionFunc ==  EnPoh_FlySideways || this->actionFunc == EnPoh_Engaging)) {
            if (this->actor.xzDistToPlayer < NearEscapeRange-10.0f)
                EnPoh_SetupFlyAway(this);
            else
                EnPoh_SetupAppear(this);
        }
    }
}

void EnPoh_Update(Actor* thisx, PlayState* play) {
    EnPoh* this = (EnPoh*)thisx;

    if (Object_IsLoaded(&play->objectCtx, this->objectIdx)) {
        this->actor.objBankIndex = this->objectIdx;
        this->actor.update = EnPoh_UpdateLiving;
        Actor_SetObjectDependency(play, &this->actor);
        if (this->infoIdx == EN_POH_INFO_NORMAL) {
            SkelAnime_Init(play, &this->skelAnime, &gPoeSkel, &gPoeFloatAnim, this->jointTable, this->morphTable,
                           21);
            this->actor.draw = EnPoh_DrawRegular;
        } else {
            SkelAnime_InitFlex(play, &this->skelAnime, &gPoeComposerSkel, &gPoeComposerFloatAnim, this->jointTable,
                               this->morphTable, 12);
            this->actor.draw = EnPoh_DrawComposer;
            this->colliderSph.elements[0].dim.limb = 9;
            this->colliderSph.elements[0].dim.modelSphere.center.y *= -1;
            this->actor.shape.rot.y = this->actor.world.rot.y = -0x4000;
            this->colliderCyl.dim.radius = 20;
            this->colliderCyl.dim.height = 55;
            this->colliderCyl.dim.yShift = 15;
        }
        this->actor.flags &= ~ACTOR_FLAG_4;
        EnPoh_SetupInitialAction(this);
    }
}

void EnPo_HandleLightColors(EnPoh* this) {
    s16 temp_var;

    if (this->actionFunc == EnPoh_Attack) {
        this->lightColor.r = CLAMP_MAX((s16)(this->lightColor.r + 5), 255);
        this->lightColor.g = CLAMP_MIN((s16)(this->lightColor.g - 5), 50);
        temp_var = this->lightColor.b - 5;
        this->lightColor.b = CLAMP_MIN(temp_var, 0);
    } else if (this->actionFunc == EnPoh_FlyAway) {
        this->lightColor.r = CLAMP_MAX((s16)(this->lightColor.r + 5), 80);
        this->lightColor.g = CLAMP_MAX((s16)(this->lightColor.g + 5), 255);
        temp_var = this->lightColor.b + 5;
        this->lightColor.b = CLAMP_MAX(temp_var, 225);
    } else if (this->actionFunc == EnPoh_RecallingFromHit) {
        if (this->actor.colorFilterTimer & 2) {
            this->lightColor.r = 0;
            this->lightColor.g = 0;
            this->lightColor.b = 0;
        } else {
            this->lightColor.r = 80;
            this->lightColor.g = 255;
            this->lightColor.b = 225;
        }
    } else {
        this->lightColor.r = CLAMP_MAX((s16)(this->lightColor.r + 5), 255);
        this->lightColor.g = CLAMP_MAX((s16)(this->lightColor.g + 5), 255);
        if (this->lightColor.b >= 211) {
            temp_var = this->lightColor.b - 5;
            this->lightColor.b = CLAMP_MIN(temp_var, 210);
        } else {
            temp_var = this->lightColor.b + 5;
            this->lightColor.b = CLAMP_MAX(temp_var, 210);
        }
    }
}

void EnPo_HandleEnvColors(EnPoh* this) {
    f32 rand;

    if ((this->actionFunc == EnPoh_NormalApparate || this->actionFunc == EnPoh_ComposerApparate) &&
        this->skelAnime.curFrame < 12.0f) {
        this->envColor.r = this->envColor.g = this->envColor.b = (s16)(this->skelAnime.curFrame * 16.66f) + 55;
        this->envColor.a = this->skelAnime.curFrame * (100.0f / 6.0f);
    } else {
        rand = Rand_ZeroOne();
        this->envColor.r = (s16)(rand * 30.0f) + 225;
        this->envColor.g = (s16)(rand * 100.0f) + 155;
        this->envColor.b = (s16)(rand * 160.0f) + 95;
        this->envColor.a = 200;
    }
}

void EnPoh_UpdateLiving(Actor* thisx, PlayState* play) {
    EnPoh* this = (EnPoh*)thisx;
    s32 pad;
    Vec3f vec;
    s32 sp38;

    if (this->colliderSph.base.atFlags & AT_HIT) {
        this->colliderSph.base.atFlags &= ~AT_HIT;
        EnPoh_SetupAttackHit(this);
    }
    EnPo_CollisionCheck(this, play);
    EnPoh_UpdateVisibility(this);
    this->actionFunc(this, play);
    Actor_MoveForward(&this->actor);
    if (this->actionFunc == EnPoh_Attack && this->actionTimer < 10) {
        this->actor.flags |= ACTOR_FLAG_24;
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->colliderSph.base);
    }
    Collider_UpdateCylinder(&this->actor, &this->colliderCyl);
    if ((this->colliderCyl.base.acFlags & AC_ON) && this->lightColor.a == 255) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->colliderCyl.base);
    }
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderCyl.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderSph.base);
    Actor_SetFocus(&this->actor, 42.0f);
    if (this->actionFunc != EnPoh_RecallingFromHit && this->actionFunc != EnPoh_AttackHit) {
        if (this->actionFunc == EnPoh_FlyAway) {
            this->actor.shape.rot.y = this->actor.world.rot.y + 0x8000;
        } else if (this->actionFunc == EnPoh_FlySideways) {
            this->actor.shape.rot.y = this->actor.world.rot.y - 0x4000*this->trackingDir;
        } else {
            this->actor.shape.rot.y = this->actor.world.rot.y;
        }
    }
    vec.x = this->actor.world.pos.x;
    vec.y = this->actor.world.pos.y + 20.0f;
    vec.z = this->actor.world.pos.z;
    this->actor.floorHeight =
        BgCheck_EntityRaycastFloor4(&play->colCtx, &this->actor.floorPoly, &sp38, &this->actor, &vec);
    EnPo_HandleEnvColors(this);
    this->actor.shape.shadowAlpha = this->lightColor.a;
}

s32 EnPoh_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx,
                           Gfx** gfxP) {
    EnPoh* this = (EnPoh*)thisx;

    if ((this->lightColor.a == 0 || limbIndex == this->info->unk_6) ||
        (this->actionFunc == EnPoh_StartDying && this->actionTimer >= 2)) {
        *dList = NULL;
    } else if (this->actor.params == EN_POH_FLAT && limbIndex == 0xA) {
        // Replace Sharp's head with Flat's
        *dList = gPoeComposerFlatHeadDL;
    }
    if (limbIndex == 0x13 && this->infoIdx == EN_POH_INFO_NORMAL) {
        gDPPipeSync((*gfxP)++);
        gDPSetEnvColor((*gfxP)++, this->lightColor.r, this->lightColor.g, this->lightColor.b, this->lightColor.a);
    }
    return false;
}

void EnPoh_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx, Gfx** gfxP) {
    EnPoh* this = (EnPoh*)thisx;

    Collider_UpdateSpheres(limbIndex, &this->colliderSph);
    if (this->actionFunc == EnPoh_StartDying && this->actionTimer >= 2 && limbIndex == this->info->unk_7) {
        gSPMatrix((*gfxP)++, MATRIX_NEWMTX(play->state.gfxCtx),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList((*gfxP)++, this->info->burnDisplayList);
    }
    if (limbIndex == this->info->unk_6) {
        if (this->actionFunc == EnPoh_StartDying && this->actionTimer >= 19 && 0.0f != this->actor.scale.x) {
            f32 mtxScale = 0.01f / this->actor.scale.x;
            Matrix_Scale(mtxScale, mtxScale, mtxScale, MTXMODE_APPLY);
        }
        Matrix_Get(&this->unk_368);
        if (this->actionFunc == EnPoh_StartDying && this->actionTimer == 27) {
            this->actor.world.pos.x = this->unk_368.xw;
            this->actor.world.pos.y = this->unk_368.yw;
            this->actor.world.pos.z = this->unk_368.zw;
        }
        Lights_PointGlowSetInfo(&this->lightInfo, this->colliderSph.elements[0].dim.worldSphere.center.x,
                                this->colliderSph.elements[0].dim.worldSphere.center.y,
                                this->colliderSph.elements[0].dim.worldSphere.center.z, this->envColor.r,
                                this->envColor.g, this->envColor.b, this->envColor.a * (200.0f / 255));
    }
}

void EnPoh_DrawRegular(Actor* thisx, PlayState* play) {
    EnPoh* this = (EnPoh*)thisx;

    OPEN_DISPS(play->state.gfxCtx);
    EnPo_HandleLightColors(this);
    func_80093D18(play->state.gfxCtx);
    func_80093D84(play->state.gfxCtx);
    if (this->lightColor.a == 255 || this->lightColor.a == 0) {
        gDPSetEnvColor(POLY_OPA_DISP++, this->lightColor.r, this->lightColor.g, this->lightColor.b, this->lightColor.a);
        gSPSegment(POLY_OPA_DISP++, 0x08, D_80116280 + 2);
        POLY_OPA_DISP = SkelAnime_Draw(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       EnPoh_OverrideLimbDraw, EnPoh_PostLimbDraw, &this->actor, POLY_OPA_DISP);
    } else {
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, this->lightColor.a);
        gSPSegment(POLY_XLU_DISP++, 0x08, D_80116280);
        POLY_XLU_DISP = SkelAnime_Draw(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       EnPoh_OverrideLimbDraw, EnPoh_PostLimbDraw, &this->actor, POLY_XLU_DISP);
    }
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetEnvColor(POLY_OPA_DISP++, this->envColor.r, this->envColor.g, this->envColor.b, 255);
    Matrix_Put(&this->unk_368);
    gSPMatrix(POLY_OPA_DISP++, MATRIX_NEWMTX(play->state.gfxCtx),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, this->info->lanternDisplayList);
    CLOSE_DISPS(play->state.gfxCtx);
}

void EnPoh_DrawComposer(Actor* thisx, PlayState* play) {
    EnPoh* this = (EnPoh*)thisx;
    Color_RGBA8* sp90;
    Color_RGBA8* phi_t0;

    OPEN_DISPS(play->state.gfxCtx);
    EnPo_HandleLightColors(this);
    if (this->actor.params == EN_POH_SHARP) {
        sp90 = &D_80AE1B4C;
        phi_t0 = &D_80AE1B54;
    } else {
        sp90 = &D_80AE1B50;
        phi_t0 = &D_80AE1B58;
    }
    if (this->lightColor.a == 255 || this->lightColor.a == 0) {
        func_80093D18(play->state.gfxCtx);
        gSPSegment(POLY_OPA_DISP++, 0x08,
                   Gfx_EnvColor(play->state.gfxCtx, this->lightColor.r, this->lightColor.g, this->lightColor.b,
                                this->lightColor.a));
        gSPSegment(POLY_OPA_DISP++, 0x0A,
                   Gfx_EnvColor(play->state.gfxCtx, sp90->r, sp90->g, sp90->b, this->lightColor.a));
        gSPSegment(POLY_OPA_DISP++, 0x0B,
                   Gfx_EnvColor(play->state.gfxCtx, phi_t0->r, phi_t0->g, phi_t0->b, this->lightColor.a));
        gSPSegment(POLY_OPA_DISP++, 0x0C, D_80116280 + 2);
        POLY_OPA_DISP = SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                           this->skelAnime.dListCount, EnPoh_OverrideLimbDraw, EnPoh_PostLimbDraw,
                                           &this->actor, POLY_OPA_DISP);
    } else {
        func_80093D18(play->state.gfxCtx);
        func_80093D84(play->state.gfxCtx);
        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_EnvColor(play->state.gfxCtx, this->lightColor.r, this->lightColor.g, this->lightColor.b,
                                this->lightColor.a));
        gSPSegment(POLY_XLU_DISP++, 0x0A,
                   Gfx_EnvColor(play->state.gfxCtx, sp90->r, sp90->g, sp90->b, this->lightColor.a));
        gSPSegment(POLY_XLU_DISP++, 0x0B,
                   Gfx_EnvColor(play->state.gfxCtx, phi_t0->r, phi_t0->g, phi_t0->b, this->lightColor.a));
        gSPSegment(POLY_XLU_DISP++, 0x0C, D_80116280);
        POLY_XLU_DISP = SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                           this->skelAnime.dListCount, EnPoh_OverrideLimbDraw, EnPoh_PostLimbDraw,
                                           &this->actor, POLY_XLU_DISP);
    }
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetEnvColor(POLY_OPA_DISP++, this->envColor.r, this->envColor.g, this->envColor.b, 255);
    Matrix_Put(&this->unk_368);
    gSPMatrix(POLY_OPA_DISP++, MATRIX_NEWMTX(play->state.gfxCtx),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, this->info->lanternDisplayList);
    gSPDisplayList(POLY_OPA_DISP++, gPoeComposerLanternBottomDL);
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetEnvColor(POLY_OPA_DISP++, sp90->r, sp90->g, sp90->b, 255);
    gSPDisplayList(POLY_OPA_DISP++, gPoeComposerLanternTopDL);
    CLOSE_DISPS(play->state.gfxCtx);
}

void EnPoh_UpdateDead(Actor* thisx, PlayState* play) {
    EnPoh* this = (EnPoh*)thisx;

    this->actionFunc(this, play);
    if (this->actionFunc != EnPoh_Death) {
        this->visibilityTimer++;
    }
    EnPo_HandleEnvColors(this);
}

void EnPoh_DrawSoul(Actor* thisx, PlayState* play) {
    EnPoh* this = (EnPoh*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    if (this->actionFunc == EnPoh_Death) {
        func_80093D18(play->state.gfxCtx);
        gDPSetEnvColor(POLY_OPA_DISP++, this->envColor.r, this->envColor.g, this->envColor.b, 255);
        Lights_PointGlowSetInfo(&this->lightInfo, this->actor.world.pos.x, this->actor.world.pos.y,
                                this->actor.world.pos.z, this->envColor.r, this->envColor.g, this->envColor.b, 200);
        gSPMatrix(POLY_OPA_DISP++, MATRIX_NEWMTX(play->state.gfxCtx),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, this->info->lanternDisplayList);
        if (this->infoIdx == EN_POH_INFO_COMPOSER) {
            Color_RGBA8* envColor = (this->actor.params == EN_POH_SHARP) ? &D_80AE1B4C : &D_80AE1B50;
            s32 pad;

            gSPDisplayList(POLY_OPA_DISP++, gPoeComposerLanternBottomDL);
            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetEnvColor(POLY_OPA_DISP++, envColor->r, envColor->g, envColor->b, 255);
            gSPDisplayList(POLY_OPA_DISP++, gPoeComposerLanternTopDL);
        }
    } else {
        func_80093D84(play->state.gfxCtx);
        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0,
                                    (this->visibilityTimer * this->info->unk_8) % 512U, 0x20, 0x80));
        gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, this->info->primColor.r, this->info->primColor.g,
                        this->info->primColor.b, this->lightColor.a);
        gDPSetEnvColor(POLY_XLU_DISP++, this->lightColor.r, this->lightColor.g, this->lightColor.b, 255);
        Matrix_RotateY((s16)(Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) + 0x8000) * 9.58738e-05f, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, MATRIX_NEWMTX(play->state.gfxCtx),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, this->info->soulDisplayList);
    }
    CLOSE_DISPS(play->state.gfxCtx);
}
