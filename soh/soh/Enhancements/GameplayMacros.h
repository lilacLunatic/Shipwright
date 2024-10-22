#pragma once
#ifndef GAMEPLAY_MACROS_H
#define GAMEPLAY_MACROS_H

#include "soh/OTRGlobals.h"
#include "libultraship/libultraship.h"
#include <z64.h>

#define MAX_MACRO_LEN 10000
typedef struct {
    Input inputs[MAX_MACRO_LEN];
    int duration;
    int playback;
} Macro;


#ifdef __cplusplus
extern "C" {
#endif
//void GameplayMacros_RefreshMacroList();
void GameplayMacros_SaveMacro(char* filePath, Macro* macro);
Macro GameplayMacros_LoadMacro(char* filePath);
#ifdef __cplusplus
}
#endif

#endif
