#pragma once

#include "Model/LightData.hpp"

namespace component {
/**
 * @struct DirectionalLight
 * @brief A directional light component.
 */
struct DirectionalLight {
	/// The directional light data.
	DirectionalLightData light_data;
};

/**
 * @struct PointLight
 * @brief A point light component.
 */
struct PointLight {
	/// The point light data.
	PointLightData light_data;
	/// The point light id in the Light manager.
	size_t light_id;
};

/**
 * @struct SpotLight
 * @brief A point light component.
 */
struct SpotLight {
	/// The spot light data.
	SpotLightData light_data;
	/// The spot light id in the Light Manager.
	size_t light_id;
};

};  // namespace component