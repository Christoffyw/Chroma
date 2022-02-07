#include "Chroma.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Mathf.hpp"
#include "UnityEngine/SpriteRenderer.hpp"
#include "UnityEngine/MaterialPropertyBlock.hpp"

#include <unordered_map>
#include "colorizer/BombColorizer.hpp"
#include "utils/ChromaUtils.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace Sombrero;
using namespace Chroma;


BombColorizer::ColorizerMap BombColorizer::Colorizers = BombColorizer::ColorizerMap();


void BombColorizer::Refresh() {
    if (BombColorable) return;
    UnityEngine::Material* bombMaterial = _bombRenderer->get_material();
    Sombrero::FastColor const& color = getColor();

    static ConstString colorName("_SimpleColor");

    if (color == static_cast<Sombrero::FastColor>(bombMaterial->GetColor(colorName))) {
        return;
    }

    bombMaterial->SetColor(colorName, color);
}

BombColorizer::BombColorizer(GlobalNamespace::NoteControllerBase *noteController) :
    _bombRenderer(noteController->get_gameObject()->GetComponentInChildren<Renderer*>())
{
    static ConstString colorName("_SimpleColor");

    OriginalColor = _bombRenderer->get_material()->GetColor(colorName);
}

std::optional<Sombrero::FastColor> BombColorizer::getGlobalColor() {
    return GlobalColor;
}

void BombColorizer::GlobalColorize(std::optional<Sombrero::FastColor> const& color) {
    GlobalColor = color;
    for (auto& [_, colorizer] : Colorizers)
    {
        colorizer.Refresh();
    }
}

BombColorizer& BombColorizer::New(GlobalNamespace::NoteControllerBase *noteController) {
    return Colorizers.try_emplace(noteController, noteController).first->second;
}

std::optional<Sombrero::FastColor> BombColorizer::GlobalColorGetter() {
    return GlobalColor;
}

void BombColorizer::Reset() {
    GlobalColor = std::nullopt;
    Colorizers.clear();
}




