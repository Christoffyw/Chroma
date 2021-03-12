#include "Chroma.hpp"

#include "ChromaController.hpp"

#include "colorizer/NoteColorizer.hpp"
#include "utils/ChromaUtils.hpp"

using namespace GlobalNamespace;
using namespace Chroma;

MAKE_HOOK_OFFSETLESS(ColorNoteVisuals_HandleNoteControllerDidInit, void, ColorNoteVisuals* self, NoteController* noteController) {
    // Do nothing if Chroma shouldn't run
    if (!ChromaController::DoChromaHooks()) {
        ColorNoteVisuals_HandleNoteControllerDidInit(self, noteController);
        return;
    }

    NoteColorizer::CNVStart(self, noteController);


    if (noteController->noteData && il2cpp_functions::class_is_assignable_from(noteController->noteData->klass, classof(CustomJSONData::CustomNoteData*))) {
        auto *pCustomNoteData = reinterpret_cast<CustomJSONData::CustomNoteData *>(noteController->noteData);

        if (pCustomNoteData->customData && pCustomNoteData->customData->value) {
            rapidjson::Value* dynData = pCustomNoteData->customData->value;

            std::optional<UnityEngine::Color> color = ChromaUtils::ChromaUtilities::GetColorFromData(dynData);

            if (color)
            {
                NoteColorizer::SetNoteColors(noteController, color.value(), color.value());
                pCustomNoteData->customData->associatedData['C'] = new CustomData::NoteData {
                    color.value(),
                    color.value()
                };
            }
            else
            {
                NoteColorizer::Reset(noteController);
            }
        }
    }

    NoteColorizer::EnableNoteColorOverride(noteController);

    ColorNoteVisuals_HandleNoteControllerDidInit(self, noteController);

    NoteColorizer::DisableNoteColorOverride();
}

void Chroma::Hooks::ColorNoteVisuals() {
    INSTALL_HOOK_OFFSETLESS(getLogger(), ColorNoteVisuals_HandleNoteControllerDidInit, il2cpp_utils::FindMethodUnsafe("", "ColorNoteVisuals", "HandleNoteControllerDidInit", 1));
}