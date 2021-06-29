#include "Chroma.hpp"
#include "ChromaController.hpp"

#include "lighting/environment_enhancements/ParametricBoxControllerParameters.hpp"

#include "colorizer/ObstacleColorizer.hpp"
#include "GlobalNamespace/ColorManager.hpp"
#include "custom-json-data/shared/CustomBeatmapData.h"
#include "GlobalNamespace/ObstacleController.hpp"
#include "GlobalNamespace/ParametricBoxController.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/MaterialPropertyBlock.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "utils/ChromaUtils.hpp"

#include "ChromaObjectData.hpp"

using namespace CustomJSONData;
using namespace GlobalNamespace;
using namespace Chroma;
using namespace ChromaUtils;


UnityEngine::Vector3& GetTransformScale(UnityEngine::Vector3& defaultV, ParametricBoxControllerParameters& parameters) {

    if (parameters.Position) {
        return parameters.Scale.value();
    }

    return defaultV;
}

UnityEngine::Vector3& GetTransformPosition(UnityEngine::Vector3& defaultV, ParametricBoxControllerParameters& parameters) {

    if (parameters.Position) {
        return parameters.Position.value();
    }

    return defaultV;
}

MAKE_HOOK_OFFSETLESS(ParametricBoxController_Refresh,void, ParametricBoxController* self) {
    // Do nothing if Chroma shouldn't run
    if (!ChromaController::DoChromaHooks()) {
        ParametricBoxController_Refresh(self);
        return;
    }

    if (self->meshRenderer == nullptr)
    {
        return;
    }

    auto scale = UnityEngine::Vector3(self->width * 0.5f, self->height * 0.5f, self->length * 0.5f);
    auto pos = UnityEngine::Vector3(0.0f, (0.5f - self->heightCenter) * self->height, 0.0f);



    auto it = ParametricBoxControllerParameters::TransformParameters.find(self);

    if (it != ParametricBoxControllerParameters::TransformParameters.end()) {
        scale = GetTransformScale(scale, it->second);
        pos = GetTransformPosition(pos, it->second);
    }

    self->get_transform()->set_localScale(scale);
    self->get_transform()->set_localPosition(pos);

    static auto materialPropertyBlock = ParametricBoxController::_get__materialPropertyBlock();

    if (materialPropertyBlock == nullptr) {
        ParametricBoxController::_set__materialPropertyBlock(UnityEngine::MaterialPropertyBlock::New_ctor());
        materialPropertyBlock = ParametricBoxController::_get__materialPropertyBlock();
    }


    auto color = self->color;
    color.a *= self->alphaMultiplier;
    if (color.a < self->minAlpha)
    {
        color.a = self->minAlpha;
    }

    static auto colorId = ParametricBoxController::_get__colorID();
    static auto alphaStartID = ParametricBoxController::_get__alphaStartID();
    static auto alphaEndID = ParametricBoxController::_get__alphaEndID();
    static auto widthStartID = ParametricBoxController::_get__widthStartID();
    static auto widthEndID = ParametricBoxController::_get__widthEndID();

    materialPropertyBlock->SetColor(colorId, color);
    materialPropertyBlock->SetFloat(alphaStartID, self->alphaStart);
    materialPropertyBlock->SetFloat(alphaEndID, self->alphaEnd);
    materialPropertyBlock->SetFloat(widthStartID, self->widthStart);
    materialPropertyBlock->SetFloat(widthEndID, self->widthEnd);
    self->meshRenderer->SetPropertyBlock(materialPropertyBlock);

}

void ParametricBoxControllerHook(Logger& logger) {
    INSTALL_HOOK_OFFSETLESS(logger, ParametricBoxController_Refresh, il2cpp_utils::FindMethodUnsafe("", "ParametricBoxController", "Refresh", 0));
}

ChromaInstallHooks(ParametricBoxControllerHook)