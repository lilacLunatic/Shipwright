#pragma once
#include <libultraship/libultraship.h>

// Not to be confused with tabs, groups are 1:1 with the boxes shown in the UI, grouping them allows us to
// reset/randomize every item in a group at once. If you are looking for tabs they are rendered manually in ImGui in
// `DrawCosmeticsEditor`
typedef enum {
    COSMETICS_GROUP_LINK,
    COSMETICS_GROUP_MIRRORSHIELD,
    COSMETICS_GROUP_SWORDS,
    COSMETICS_GROUP_GLOVES,
    COSMETICS_GROUP_EQUIPMENT,
    COSMETICS_GROUP_KEYRING,
    COSMETICS_GROUP_SMALL_KEYS,
    COSMETICS_GROUP_BOSS_KEYS,
    COSMETICS_GROUP_CONSUMABLE,
    COSMETICS_GROUP_HUD,
    COSMETICS_GROUP_KALEIDO,
    COSMETICS_GROUP_TITLE,
    COSMETICS_GROUP_NPC,
    COSMETICS_GROUP_WORLD,
    COSMETICS_GROUP_MAGIC,
    COSMETICS_GROUP_ARROWS,
    COSMETICS_GROUP_SPIN_ATTACK,
    COSMETICS_GROUP_TRAILS,
    COSMETICS_GROUP_NAVI,
    COSMETICS_GROUP_IVAN,
    COSMETICS_GROUP_MESSAGE,
    COSMETICS_GROUP_MAX,
} CosmeticGroup;

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

Color_RGBA8 CosmeticsEditor_GetDefaultValue(const char* id);

#ifdef __cplusplus
}

typedef struct {
    const std::string Name;
    const std::string ToolTip;
    const std::string CvarName;
    ImVec4 ModifiedColor;
    ImVec4 DefaultColor;
    bool canRainbow;
    bool hasAlpha;
    bool sameLine;
} CosmeticsColorIndividual;

static float TablesCellsWidth = 300.0f;
static ImGuiTableColumnFlags FlagsTable = ImGuiTableFlags_BordersH | ImGuiTableFlags_BordersV;
static ImGuiTableColumnFlags FlagsCell =
    ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_IndentEnable | ImGuiTableColumnFlags_NoSort;

void CosmeticsEditor_RandomizeAll();
void CosmeticsEditor_RandomizeGroup(CosmeticGroup group);
void CosmeticsEditor_ResetAll();
void CosmeticsEditor_ResetGroup(CosmeticGroup group);
void ApplyOrResetCustomGfxPatches(bool manualChange = true);

class CosmeticsEditorWindow final : public Ship::GuiWindow {
  public:
    using GuiWindow::GuiWindow;

    void InitElement() override;
    void DrawElement() override;
    void ApplyDungeonKeyColors();
    void UpdateElement() override{};
};

const size_t RAINBOW_PRESET_LEN = 9;

static const char* RAINBOW_PRESET_NAMES[RAINBOW_PRESET_LEN] = {
     "Christmas",
     "Transgender",
     "Nonbinary",
     "Bisexual",
     "Lesbian",
     "Gay (MLM)",
     "Asexual",
     "Brazil",
     "Italy"
};

static const ImVec4 RAINBOW_PRESETS[RAINBOW_PRESET_LEN][4] = {
    { //christmas
        {0.0/255.0, 140.0/255.0, 69.0/255.0, 0},
        {205.0/255.0, 33.0/255.0, 42.0/255.0, 0},
        {0.0/255.0, 140.0/255.0, 69.0/255.0, 0},
        {205.0/255.0, 33.0/255.0, 42.0/255.0, 0}
    },
    { //trans
        {255.0/255.0, 255.0/255.0, 255.0/255.0, 0},
        {255.0/255.0, 159.0/255.0, 186.0/255.0, 0},
        {255.0/255.0, 255.0/255.0, 255.0/255.0, 0},
        {71.0/255.0, 186.0/255.0, 230.0/255.0, 0}
    },

    { //enby
        {252.0/255.0, 244.0/255.0, 52.0/255.0, 0},
        {255.0/255.0, 255.0/255.0, 255.0/255.0, 0},
        {156.0/255.0, 89.0/255.0, 209.0/255.0, 0},
        {0.0/255.0, 0.0/255.0, 0.0/255.0, 0}
    },

    { //bi
        {155.0/255.0, 79.0/255.0, 150.0/255.0, 0},
        {0.0/255.0, 56.0/255.0, 168.0/255.0, 0},
        {155.0/255.0, 79.0/255.0, 150.0/255.0, 0},
        {214.0/255.0, 2.0/255.0, 112.0/255.0, 0}
    },

    { //lesbian
        {255.0/255.0, 255.0/255.0, 255.0/255.0, 0},
        {213.0/255.0, 45.0/255.0, 0.0/255.0, 0},
        {255.0/255.0, 255.0/255.0, 255.0/255.0, 0},
        {163.0/255.0, 2.0/255.0, 98.0/255.0, 0}
    },

    { //gay
        {7.0/255.0, 141.0/255.0, 112.0/255.0, 0},
        {255.0/255.0, 255.0/255.0, 255.0/255.0, 0},
        {123.0/255.0, 173.0/255.0, 226.0/255.0, 0},
        {61.0/255.0, 26.0/255.0, 120.0/255.0, 0}
    },

    { //ace
        {0.0/255.0, 0.0/255.0, 0.0/255.0, 0},
        {163.0/255.0, 163.0/255.0, 163.0/255.0, 0},
        {255.0/255.0, 255.0/255.0, 255.0/255.0, 0},
        {128.0/255.0, 0.0/255.0, 128.0/255.0, 0}
    },

    { //br
        {0.0/255.0, 151.0/255.0, 57.0/255.0, 0},
        {254.0/255.0, 221.0/255.0, 0.0/255.0, 0},
        {255.0/255.0, 255.0/255.0, 255.0/255.0, 0},
        {1.0/255.0, 33.0/255.0, 105.0/255.0, 0}
    },

    { //it
        {255.0/255.0, 255.0/255.0, 255.0/255.0, 0},
        {0.0/255.0, 140.0/255.0, 69.0/255.0, 0},
        {255.0/255.0, 255.0/255.0, 255.0/255.0, 0},
        {205.0/255.0, 33.0/255.0, 42.0/255.0, 0}
    }

};

#endif //__cplusplus
