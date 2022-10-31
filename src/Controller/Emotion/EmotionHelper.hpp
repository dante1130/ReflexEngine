#pragma once

#include "Controller/ECS/Entity.hpp"

namespace Emotion {
/**
 * @brief Updates the emotions using the utility contexts.
 *
 * @param entity The entity to update.
 */
auto update_emotion(const Reflex::Entity& entity) -> void;
}  // namespace Emotion