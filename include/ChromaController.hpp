#pragma once

#include "custom-types/shared/coroutine.hpp"
#include "GlobalNamespace/BeatmapObjectSpawnController.hpp"
#include "GlobalNamespace/BeatmapCallbacksController.hpp"

#include "custom-types/shared/types.hpp"
#include "custom-types/shared/macros.hpp"

#include "System/Collections/Generic/IEnumerator_1.hpp"

#include "UnityEngine/WaitForEndOfFrame.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"

#include "main.hpp"
#include "utils/XoshiroCpp.hpp"

#include <random>

namespace Chroma {
    typedef rapidjson::GenericDocument<rapidjson::UTF16<char16_t>> DocumentUTF16;

    class ChromaController {
    private:
        static bool ChromaLegacy;
        static bool ChromaMap;
        static std::unordered_set<std::string> ModsForcingDoHooks;

    public:
        static bool TutorialMode;
        inline static XoshiroCpp::Xoshiro128PlusPlus randomizerThing;

        // probably belongs in utils but whatever
        static inline auto randomXoshiro(float min = 0, float max = 1.0f) {
            std::uniform_real_distribution<float> distr(min, max);

            return distr(randomizerThing);
        }

        // Return true if Chroma should color the sabers
        // Practically the same as DoChromaHooks, so yeet?
        static bool DoColorizerSabers() {
            return ChromaRequired() && getChromaConfig().customNoteColors.GetValue();
        }

        // Return true if Chroma is required/suggested in a map
        static bool ChromaRequired() {
            return (!TutorialMode && ChromaMap) || !ModsForcingDoHooks.empty();
        }

        static void setChromaRequired(bool chromaMap);

        // Return true if Chroma hooks should run
        static bool DoChromaHooks() {
            return getChromaConfig().customColorEventsEnabled.GetValue() && (ChromaRequired());
        }

        static void AddForceDoHooks(ModInfo const& otherModInfo);
        static void RemoveForceDoHooks(ModInfo const& otherModInfo);

        // Quest internal stuff
        static void SetChromaLegacy(bool v);

        static bool GetChromaLegacy() {
            return ChromaLegacy;
        }

        inline static GlobalNamespace::BeatmapObjectSpawnController* BeatmapObjectSpawnController = nullptr;
        inline static GlobalNamespace::BeatmapCallbacksController* CallbacksController = nullptr;

        // internal
        static void OnActiveSceneChanged(UnityEngine::SceneManagement::Scene current);

        static custom_types::Helpers::Coroutine DelayedStartEnumerator(GlobalNamespace::BeatmapObjectSpawnController *beatmapObjectSpawnController);

        // Since level data is freed on scene load, we copy it before we load.
        inline static std::optional<DocumentUTF16> infoDatCopy = std::nullopt;
    };
}