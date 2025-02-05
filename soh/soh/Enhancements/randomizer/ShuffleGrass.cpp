#include "ShuffleGrass.h"
#include "soh_assets.h"
#include "static_data.h"

extern "C" {
#include "variables.h"
#include "overlays/actors/ovl_En_Kusa/z_en_kusa.h"
#include "objects/gameplay_field_keep/gameplay_field_keep.h"
#include "objects/object_kusa/object_kusa.h"
extern PlayState* gPlayState;
}

#define RAND_GET_OPTION(option) Rando::Context::GetInstance()->GetOption(option).Get()

extern void EnItem00_DrawRandomizedItem(EnItem00* enItem00, PlayState* play);

extern "C" void EnKusa_RandomizerDraw(Actor* thisx, PlayState* play) {
    static Gfx* dLists[] = { (Gfx*)gFieldBushDL, (Gfx*)object_kusa_DL_000140, (Gfx*)object_kusa_DL_000140 };
    auto grassActor = ((EnKusa*)thisx);

    OPEN_DISPS(play->state.gfxCtx);
    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    gDPSetGrayscaleColor(POLY_OPA_DISP++, 175, 255, 0, 255);

    if (grassActor->grassIdentity.randomizerCheck != RC_MAX &&
        Flags_GetRandomizerInf(grassActor->grassIdentity.randomizerInf) == 0) {
        gSPGrayscale(POLY_OPA_DISP++, true);
    }

    if (grassActor->actor.flags & ACTOR_FLAG_GRASS_DESTROYED) {
        Gfx_DrawDListOpa(play, (Gfx*)object_kusa_DL_0002E0);
    } else {
        Gfx_DrawDListOpa(play, dLists[grassActor->actor.params & 3]);
    }

    gSPGrayscale(POLY_OPA_DISP++, false);

    CLOSE_DISPS(play->state.gfxCtx);
}

uint8_t EnKusa_RandomizerHoldsItem(EnKusa* grassActor, PlayState* play) {
    if (grassActor->grassIdentity.randomizerCheck == RC_MAX)
        return false;

    RandomizerCheck rc = grassActor->grassIdentity.randomizerCheck;

    uint8_t isDungeon = Rando::StaticData::GetLocation(rc)->IsDungeon();
    uint8_t grassSetting = Rando::Context::GetInstance()->GetOption(RSK_SHUFFLE_GRASS).Get();

    // Don't pull randomized item if grass isn't randomized or is already checked
    if (!IS_RANDO || (grassSetting == RO_SHUFFLE_GRASS_OVERWORLD && isDungeon) ||
        (grassSetting == RO_SHUFFLE_GRASS_DUNGEONS && !isDungeon) ||
        Flags_GetRandomizerInf(grassActor->grassIdentity.randomizerInf) ||
        grassActor->grassIdentity.randomizerCheck == RC_UNKNOWN_CHECK) {
        return false;
    } else {
        return true;
    }
}

void EnKusa_RandomizerSpawnCollectible(EnKusa* grassActor, PlayState* play) {
    EnItem00* item00 = (EnItem00*)Item_DropCollectible2(play, &grassActor->actor.world.pos, ITEM00_SOH_DUMMY);
    item00->randoInf = grassActor->grassIdentity.randomizerInf;
    item00->itemEntry =
        Rando::Context::GetInstance()->GetFinalGIEntry(grassActor->grassIdentity.randomizerCheck, true, GI_NONE);
    item00->actor.draw = (ActorFunc)EnItem00_DrawRandomizedItem;
    item00->actor.velocity.y = 8.0f;
    item00->actor.speedXZ = 2.0f;
    item00->actor.world.rot.y = Rand_CenteredFloat(65536.0f);
}

void EnKusa_RandomizerInit(void* actorRef) {
    Actor* actor = static_cast<Actor*>(actorRef);

    if (actor->id != ACTOR_EN_KUSA)
        return;

    EnKusa* grassActor = static_cast<EnKusa*>(actorRef);
    s16 respawnData = gSaveContext.respawn[RESPAWN_MODE_RETURN].data & ((1 << 8) - 1);

    grassActor->grassIdentity = OTRGlobals::Instance->gRandomizer->IdentifyGrass(
        gPlayState->sceneNum, (s16)actor->world.pos.x, (s16)actor->world.pos.z, respawnData, gPlayState->linkAgeOnLoad);
}

void RegisterShuffleGrass() {
    bool shouldRegister = IS_RANDO && RAND_GET_OPTION(RSK_SHUFFLE_GRASS);

    COND_ID_HOOK(OnActorInit, ACTOR_EN_KUSA, shouldRegister, EnKusa_RandomizerInit);

    COND_VB_SHOULD(VB_GRASS_SETUP_DRAW, shouldRegister, {
        EnKusa* grassActor = va_arg(args, EnKusa*);
        if (EnKusa_RandomizerHoldsItem(grassActor, gPlayState)) {
            grassActor->actor.draw = (ActorFunc)EnKusa_RandomizerDraw;
            *should = false;
        } else {
            *should = true;
        }
    });

    COND_VB_SHOULD(VB_GRASS_DROP_ITEM, shouldRegister, {
        EnKusa* grassActor = va_arg(args, EnKusa*);
        if (EnKusa_RandomizerHoldsItem(grassActor, gPlayState)) {
            EnKusa_RandomizerSpawnCollectible(grassActor, gPlayState);
            grassActor->grassIdentity.randomizerCheck = RC_MAX;
            grassActor->grassIdentity.randomizerInf = RAND_INF_MAX;
            *should = false;
        } else {
            *should = true;
        }
    });
}

static RegisterShipInitFunc initFunc(RegisterShuffleGrass, { "IS_RANDO" });