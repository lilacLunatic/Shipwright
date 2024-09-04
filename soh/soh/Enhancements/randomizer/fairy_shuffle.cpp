#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "fairy_shuffle.h"

void FairyOnVanillaBehaviorHandler(GIVanillaBehavior id, bool* should, void* optionalArg) {
	if (id == VB_SPAWN_FAIRY_GROUP) {
		// TODO
	}
}

uint32_t onVanillaBehaviorHook = 0;

void FairyRegisterHooks() {
	onVanillaBehaviorHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnVanillaBehavior>(FairyOnVanillaBehaviorHandler);
}

void FairyUnregisterHooks() {
    GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnVanillaBehavior>(onVanillaBehaviorHook);

    onVanillaBehaviorHook = 0;
}