#include "GameplayMacros.h"
#include <fstream>

static std::vector<const char*> macroFiles;
const std::filesystem::path macroFolderPath(Ship::Context::GetPathRelativeToAppDirectory("macros", appShortName));

void GameplayMacros_RefreshMacroList() {
    macroFiles.clear();
    if (!std::filesystem::exists(macroFolderPath)) {
        std::filesystem::create_directory(macroFolderPath);
    }

    int macroFileIndex = -1;

    for (const auto& entry : std::filesystem::directory_iterator(macroFolderPath)) {
        if (entry.is_regular_file()) {
            std::string fileName = entry.path().filename().string();
            macroFiles.push_back(fileName.c_str());

            // Check if the current file is the one set in the cvar
            if (fileName == CVarGetString("Macro.File", "")) {
                macroFileIndex = macroFiles.size() - 1;
            }
        }
    }

    if (macroFileIndex == -1) {
        CVarSetInteger("Macro.FileIndex", 0);
        CVarSetString("Macro.File", "");
    }
}

Macro GameplayMacros_LoadMacro(char* filePath){
    std::ifstream stream{macroFolderPath / std::string(filePath)};
    Macro result{};
    if (!stream) {
        return result;
    }
    nlohmann::json macroJson;
    macroJson << stream;
    for(auto input : macroJson["frames"]){
        result.inputs[result.duration].cur.button = input["cur"]["button"];
        result.inputs[result.duration].cur.stick_x = input["cur"]["stick_x"];
        result.inputs[result.duration].cur.stick_y = input["cur"]["stick_y"];
        result.inputs[result.duration].cur.err_no = input["cur"]["err_no"];
        result.inputs[result.duration].cur.right_stick_x = input["cur"]["right_stick_x"];
        result.inputs[result.duration].cur.right_stick_y = input["cur"]["right_stick_y"];

        result.inputs[result.duration].prev.button = input["prev"]["button"];
        result.inputs[result.duration].prev.stick_x = input["prev"]["stick_x"];
        result.inputs[result.duration].prev.stick_y = input["prev"]["stick_y"];
        result.inputs[result.duration].prev.err_no = input["prev"]["err_no"];
        result.inputs[result.duration].prev.right_stick_x = input["prev"]["right_stick_x"];
        result.inputs[result.duration].prev.right_stick_y = input["prev"]["right_stick_y"];

        result.inputs[result.duration].press.button = input["press"]["button"];
        result.inputs[result.duration].press.stick_x = input["press"]["stick_x"];
        result.inputs[result.duration].press.stick_y = input["press"]["stick_y"];
        result.inputs[result.duration].press.err_no = input["press"]["err_no"];
        result.inputs[result.duration].press.right_stick_x = input["press"]["right_stick_x"];
        result.inputs[result.duration].press.right_stick_y = input["press"]["right_stick_y"];

        result.inputs[result.duration].rel.button = input["rel"]["button"];
        result.inputs[result.duration].rel.stick_x = input["rel"]["stick_x"];
        result.inputs[result.duration].rel.stick_y = input["rel"]["stick_y"];
        result.inputs[result.duration].rel.err_no = input["rel"]["err_no"];
        result.inputs[result.duration].rel.right_stick_x = input["rel"]["right_stick_x"];
        result.inputs[result.duration].rel.right_stick_y = input["rel"]["right_stick_y"];

        if (++result.duration >= MAX_MACRO_LEN){
            break;
        }
    }
    return result;
}

void GameplayMacros_SaveMacro(char* filePath, Macro* macro){
    std::ofstream stream{macroFolderPath / std::filesystem::path(filePath)};
    if (!stream) {
        return;
    }
    nlohmann::json macroJson;
    macroJson["frames"] = {};
    for (size_t i = 0; i < macro->duration; i++) {
        Input* input = &macro->inputs[i];

        macroJson["frames"][i]["cur"]["button"] = input->cur.button;
        macroJson["frames"][i]["cur"]["stick_x"] = input->cur.stick_x;
        macroJson["frames"][i]["cur"]["stick_y"] = input->cur.stick_y;
        macroJson["frames"][i]["cur"]["err_no"] = input->cur.err_no;
        macroJson["frames"][i]["cur"]["right_stick_x"] = input->cur.right_stick_x;
        macroJson["frames"][i]["cur"]["right_stick_y"] = input->cur.right_stick_y;

        macroJson["frames"][i]["prev"]["button"] = input->prev.button;
        macroJson["frames"][i]["prev"]["stick_x"] = input->prev.stick_x;
        macroJson["frames"][i]["prev"]["stick_y"] = input->prev.stick_y;
        macroJson["frames"][i]["prev"]["err_no"] = input->prev.err_no;
        macroJson["frames"][i]["prev"]["right_stick_x"] = input->prev.right_stick_x;
        macroJson["frames"][i]["prev"]["right_stick_y"] = input->prev.right_stick_y;

        macroJson["frames"][i]["press"]["button"] = input->press.button;
        macroJson["frames"][i]["press"]["stick_x"] = input->press.stick_x;
        macroJson["frames"][i]["press"]["stick_y"] = input->press.stick_y;
        macroJson["frames"][i]["press"]["err_no"] = input->press.err_no;
        macroJson["frames"][i]["press"]["right_stick_x"] = input->press.right_stick_x;
        macroJson["frames"][i]["press"]["right_stick_y"] = input->press.right_stick_y;

        macroJson["frames"][i]["rel"]["button"] = input->rel.button;
        macroJson["frames"][i]["rel"]["stick_x"] = input->rel.stick_x;
        macroJson["frames"][i]["rel"]["stick_y"] = input->rel.stick_y;
        macroJson["frames"][i]["rel"]["err_no"] = input->rel.err_no;
        macroJson["frames"][i]["rel"]["right_stick_x"] = input->rel.right_stick_x;
        macroJson["frames"][i]["rel"]["right_stick_y"] = input->rel.right_stick_y;
    }

    stream << macroJson;
}
