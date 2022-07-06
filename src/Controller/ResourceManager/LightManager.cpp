#include "LightManager.hpp"

void LightManager::set_directional_light(
    const DirectionalLightData& light_data) {
	directional_light_ =
	    DirectionalLight(light_data.color, light_data.ambient_intensity,
	                     light_data.direction, light_data.diffuse_intensity);
}

size_t LightManager::add_point_light(const PointLightData& light_data) {
	const size_t id = get_next_point_light_id();

	point_lights_[id] = PointLight(
	    light_data.color, light_data.ambient_intensity,
	    light_data.diffuse_intensity, light_data.position, light_data.constant,
	    light_data.linear, light_data.quadratic);

	return id;
}

size_t LightManager::add_spot_light(const SpotLightData& light_data) {
	const size_t id = get_next_spot_light_id();

	spot_lights_[id] =
	    SpotLight(light_data.color, light_data.ambient_intensity,
	              light_data.diffuse_intensity, light_data.position,
	              light_data.direction, light_data.constant, light_data.linear,
	              light_data.quadratic, light_data.edge);

	return id;
}

void LightManager::update_directional_light(
    const DirectionalLightData& light_data) {
	directional_light_.set_directional_light(
	    light_data.color, light_data.ambient_intensity, light_data.direction,
	    light_data.diffuse_intensity);
}

void LightManager::update_point_light(size_t id,
                                      const PointLightData& light_data) {
	point_lights_.at(id).set_point_light(
	    light_data.color, light_data.ambient_intensity,
	    light_data.diffuse_intensity, light_data.position, light_data.constant,
	    light_data.linear, light_data.quadratic);
}

void LightManager::update_spot_lights(size_t id,
                                      const SpotLightData& light_data) {
	spot_lights_.at(id).set_spot_light(
	    light_data.color, light_data.ambient_intensity,
	    light_data.diffuse_intensity, light_data.position, light_data.direction,
	    light_data.constant, light_data.linear, light_data.quadratic,
	    light_data.edge);
}

void LightManager::delete_point_light(size_t id) {
	point_lights_.at(id) = PointLight();
}

void LightManager::delete_spot_light(size_t id) {
	spot_lights_.at(id) = SpotLight();
}

size_t LightManager::get_next_point_light_id() {
	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++) {
		if (!point_lights_.at(i).is_active()) {
			return i;
		}
	}

	return -1;
}

size_t LightManager::get_next_spot_light_id() {
	for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++) {
		if (!spot_lights_.at(i).is_active()) {
			return i;
		}
	}

	return -1;
}