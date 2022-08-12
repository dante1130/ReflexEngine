#include "Light.hpp"

#include <glad/glad.h>

Light::Light(glm::vec3 color, GLfloat aIntensity, GLfloat dIntensity)
    : m_color(color),
      m_ambientIntensity(aIntensity),
      m_diffuseIntensity(dIntensity),
      is_active_(true) {}

bool Light::is_active() const { return is_active_; }