#include "Light.hpp"

#include <glad/glad.h>

Light::Light(glm::vec3 color, GLfloat aIntensity, GLfloat dIntensity,
             const glm::mat4& light_projection)
    : m_color(color),
      m_ambientIntensity(aIntensity),
      m_diffuseIntensity(dIntensity),
      light_projection_(light_projection),
      is_active_(true) {}

bool Light::is_active() const { return is_active_; }