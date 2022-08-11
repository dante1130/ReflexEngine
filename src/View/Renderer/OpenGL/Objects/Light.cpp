#include "Light.hpp"

#include <glad/glad.h>

Light::Light(GLuint shadow_width, GLuint shadow_height, glm::vec3 color,
             GLfloat aIntensity, GLfloat dIntensity)
    : m_color(color),
      m_ambientIntensity(aIntensity),
      m_diffuseIntensity(dIntensity),
      is_active_(true) {
	shadow_map_.init(shadow_width, shadow_height);
}

const ShadowMap& Light::get_shadow_map() const { return shadow_map_; }

bool Light::is_active() const { return is_active_; }