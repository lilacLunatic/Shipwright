#ifndef SHUFFLEPOTS_H
#define SHUFFLEPOTS_H

#include "z64.h"

#ifdef __cplusplus
extern "C" {
#endif
void ObjTsubo_RandomizerDraw(Actor* potActor, PlayState* play);
void RegisterShufflePots();
#ifdef __cplusplus
};
#endif

#endif //SHUFFLEPOTS_H
