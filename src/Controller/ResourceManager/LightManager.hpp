#pragma once

#include <array>

#include "CommonValues.hpp"
#include "View/Renderer/OpenGL/Objects/DirectionalLight.hpp"
#include "View/Renderer/OpenGL/Objects/PointLight.hpp"
#include "View/Renderer/OpenGL/Objects/SpotLight.hpp"
#include "Model/LightData.hpp"
#include "Model/Components/Light.hpp"

/**
 * @class LightManager
 * @brief The light manager is used to manage the resources regarding lights.
 */
class LightManager {
public:
	LightManager() = default;

	/**
	 * @brief Set the directional light.
	 *
	 * @param light_data The light data.
	 */
	void set_directional_light(const DirectionalLightData& light_data);

	/**
	 * @brief Set the directional light.
	 *
	 * @param light The light component.
	 */
	void set_directional_light(const Component::DirectionalLight& light);

	/**
	 * @brief Add a point light.
	 *
	 * @param light_data The light data.
	 * @return size_t
	 */
	size_t add_point_light(const PointLightData& light_data);

	/**
	 * @brief Add a point light.
	 *
	 * @param light The light component.
	 * @return size_t
	 */
	size_t add_point_light(const Component::PointLight& light);

	/**
	 * @brief Add a spot light.
	 *
	 * @param light_data The light data.
	 * @return size_t
	 */
	size_t add_spot_light(const SpotLightData& light_data);

	/**
	 * @brief Add a spot light.
	 *
	 * @param light The light component.
	 * @return size_t
	 */
	size_t add_spot_light(const Component::SpotLight& light);

	/**
	 * @brief Update the directional light.
	 *
	 * @param light_data The light data.
	 */
	void update_directional_light(const DirectionalLightData& light_data);

	/**
	 * @brief Update the directional light.
	 *
	 * @param light The light component.
	 */
	void update_directional_light(const Component::DirectionalLight& light);

	/**
	 * @brief Update the point light given the id.
	 *
	 * @param id The id.
	 * @param light_data The light data.
	 */
	void update_point_light(size_t id, const PointLightData& light_data);

	/**
	 * @brief Update the point light given the id.
	 *
	 * @param id The id.
	 * @param light The light component.
	 */
	void update_point_light(size_t id, const Component::PointLight& light);

	/**
	 * @brief Update the spot light given the id.
	 *
	 * @param id The id.
	 * @param light_data The light data.
	 */
	void update_spot_light(size_t id, const SpotLightData& light_data);

	/**
	 * @brief Update the spot light given the id.
	 *
	 * @param id The id.
	 * @param light The light component.
	 */
	void update_spot_light(size_t id, const Component::SpotLight& light);

	/**
	 * @brief Delete the point light given the id.
	 *
	 * @param id The id.
	 */
	void delete_point_light(size_t id);

	/**
	 * @brief Delete the spot light given the id.
	 *
	 * @param id The id.
	 */
	void delete_spot_light(size_t id);

	/**
	 * @brief Delete all point lights.
	 */
	void delete_all_point_lights();

	/**
	 * @brief Delete all spot lights.
	 */
	void delete_all_spot_lights();

	/**
	 * @brief Get the directional light.
	 *
	 * @return const DirectionalLight&
	 */
	const DirectionalLight& get_directional_light() const;

	/**
	 * @brief Get the point lights array.
	 *
	 * @return const std::array<PointLight, MAX_POINT_LIGHTS>&
	 */
	const std::array<PointLight, MAX_POINT_LIGHTS>& get_point_lights() const;

	/**
	 * @brief Get the spot lights array.
	 *
	 * @return const std::array<SpotLight, MAX_SPOT_LIGHTS>&
	 */
	const std::array<SpotLight, MAX_SPOT_LIGHTS>& get_spot_lights() const;

private:
	/**
	 * @brief Get the next available point light id.
	 *
	 * @return size_t
	 */
	size_t get_next_point_light_id();

	/**
	 * @brief Get the next available spot light id object
	 *
	 * @return size_t
	 */
	size_t get_next_spot_light_id();

	/// The directional light.
	DirectionalLight directional_light_;
	/// The point lights array.
	std::array<PointLight, MAX_POINT_LIGHTS> point_lights_;
	/// The spot lights array.
	std::array<SpotLight, MAX_SPOT_LIGHTS> spot_lights_;
};