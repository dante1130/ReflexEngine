#pragma once

#include "Controller/ECS/Entity.hpp"

namespace Emotion {
/**
 * @brief Updates the emotions using the utility contexts, the value of each
 * context is mapped and multiplied by the weight of the context of arousal or
 * valence.
 *
 * @param entity The entity to update.
 */
auto update_emotion(const Reflex::Entity& entity) -> void;
}  // namespace Emotion