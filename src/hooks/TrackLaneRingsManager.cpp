#include "main.hpp"
#include "Chroma.hpp"
#include "ChromaController.hpp"

#include "lighting/environment_enhancements/ComponentInitializer.hpp"
#include "hooks/TrackLaneRingsManager.hpp"

#include "GlobalNamespace/TrackLaneRingsManager.hpp"

using namespace Chroma;

std::vector<GlobalNamespace::TrackLaneRingsManager*> TrackLaneRingsManagerHolder::RingManagers = std::vector<GlobalNamespace::TrackLaneRingsManager*>();

MAKE_HOOK_OFFSETLESS(TrackLaneRingsManager_Awake, void, GlobalNamespace::TrackLaneRingsManager* self) {
    // Do nothing if Chroma shouldn't run
    if (!ChromaController::DoChromaHooks()) {
        TrackLaneRingsManager_Awake(self);
        return;
    }

    if (ComponentInitializer::SkipAwake) {
        return;
    }

    TrackLaneRingsManager_Awake(self);
    TrackLaneRingsManagerHolder::RingManagers.push_back(self);
}

void Hooks::TrackLaneRingsManager() {
    INSTALL_HOOK_OFFSETLESS(getLogger(), TrackLaneRingsManager_Awake, il2cpp_utils::FindMethodUnsafe("", "TrackLaneRingsManager", "Awake", 0));
//    INSTALL_HOOK_OFFSETLESS(getLogger(), SaberManager_Finalize, il2cpp_utils::FindMethodUnsafe("System", "Object", "Finalize", 0));
}