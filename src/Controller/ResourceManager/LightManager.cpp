#include "LightManager.hpp"

void LightManager::set_directional_light(
    const DirectionalLightData& light_data) {
	directional_light_ =
	    DirectionalLight(light_data.color, light_data.ambient_intensity,
	                     light_data.direction, light_data.diffuse_intensity);
}

void LightManager::set_directional_light(
    const Component::DirectionalLight& light) {
	directional_light_ =
	    DirectionalLight(light.color, light.ambient_intensity, light.direction,
	                     light.diffuse_intensity);
}

size_t LightManager::add_point_light(const PointLightData& light_data) {
	const size_t id = get_next_point_light_id();

	point_lights_[id] = PointLight(
	    light_data.color, light_data.ambient_intensity,
	    light_data.diffuse_intensity, light_data.position, light_data.constant,
	    light_data.linear, light_data.quadratic);

	return id;
}

size_t LightManager::add_point_light(const Component::PointLight& light) {
	const size_t id = get_next_point_light_id();

	point_lights_[id] = PointLight(
	    light.color, light.ambient_intensity, light.diffuse_intensity,
	    light.position, light.constant, light.linear, light.quadratic);

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

size_t LightManager::add_spot_light(const Component::SpotLight& light) {
	const size_t id = get_next_spot_light_id();

	spot_lights_[id] =
	    SpotLight(light.color, light.ambient_intensity, light.diffuse_intensity,
	              light.position, light.direction, light.constant, light.linear,
	              light.quadratic, light.edge);

	return id;
}

void LightManager::update_directional_light(
    const DirectionalLightData& light_data) {
	directional_light_.set_directional_light(
	    light_data.color, light_data.ambient_intensity, light_data.direction,
	    light_data.diffuse_intensity);
}

void LightManager::update_directional_light(
    const Component::DirectionalLight& light) {
	directional_light_.set_directional_light(
	    light.color, light.ambient_intensity, light.direction,
	    light.diffuse_intensity);
}

void LightManager::update_point_light(size_t id,
                                      const PointLightData& light_data) {
	point_lights_.at(id).set_point_light(
	    light_data.color, light_data.ambient_intensity,
	    light_data.diffuse_intensity, light_data.position, light_data.constant,
	    light_data.linear, light_data.quadratic);
}

void LightManager::update_point_light(size_t id,
                                      const Component::PointLight& light) {
	point_lights_.at(id).set_point_light(
	    light.color, light.ambient_intensity, light.diffuse_intensity,
	    light.position, light.constant, light.linear, light.quadratic);
}

void LightManager::update_spot_light(size_t id,
                                     const SpotLightData& light_data) {
	spot_lights_.at(id).set_spot_light(
	    light_data.color, light_data.ambient_intensity,
	    light_data.diffuse_intensity, light_data.position, light_data.direction,
	    light_data.constant, light_data.linear, light_data.quadratic,
	    light_data.edge);
}

void LightManager::update_spot_light(size_t id,
                                     const Component::SpotLight& light) {
	spot_lights_.at(id).set_spot_light(
	    light.color, light.ambient_intensity, light.diffuse_intensity,
	    light.position, light.direction, light.constant, light.linear,
	    light.quadratic, light.edge);
}

void LightManager::delete_point_light(size_t id) {
	point_lights_[id] = PointLight();
}

void LightManager::delete_spot_light(size_t id) {
	spot_lights_[id] = SpotLight();
}

void LightManager::delete_all_point_lights() {
	for (auto& point_light : point_lights_) {
		point_light = PointLight();
	}
}

void LightManager::delete_all_spot_lights() {
	for (auto& spot_light : spot_lights_) {
		spot_light = SpotLight();
	}
}

const DirectionalLight& LightManager::get_directional_light() const {
	return directional_light_;
}

const std::array<PointLight, MAX_POINT_LIGHTS>& LightManager::get_point_lights()
    const {
	return point_lights_;
}

const std::array<SpotLight, MAX_SPOT_LIGHTS>& LightManager::get_spot_lights()
    const {
	return spot_lights_;
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