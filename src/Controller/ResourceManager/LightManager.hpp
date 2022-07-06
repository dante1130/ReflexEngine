#pragma once

#include <array>

#include "CommonValues.hpp"
#include "View/Renderer/OpenGL/Objects/DirectionalLight.hpp"
#include "View/Renderer/OpenGL/Objects/PointLight.hpp"
#include "View/Renderer/OpenGL/Objects/SpotLight.hpp"
#include "Model/LightData.hpp"

class LightManager {
public:
	LightManager() = default;

	void set_directional_light(const DirectionalLightData& light_data);

	size_t add_point_light(const PointLightData& light_data);

	size_t add_spot_light(const SpotLightData& light_data);

	void update_directional_light(const DirectionalLightData& light_data);

	void update_point_light(size_t id, const PointLightData& light_data);

	void update_spot_lights(size_t id, const SpotLightData& light_data);

	void delete_point_light(size_t id);

	void delete_spot_light(size_t id);

	const DirectionalLight& get_directional_light() const;

	const PointLight* get_point_lights() const;

	const SpotLight* get_spot_lights() const;

private:
	size_t get_next_point_light_id();

	size_t get_next_spot_light_id();

	DirectionalLight directional_light_;
	std::array<PointLight, MAX_POINT_LIGHTS> point_lights_;
	std::array<SpotLight, MAX_SPOT_LIGHTS> spot_lights_;
};