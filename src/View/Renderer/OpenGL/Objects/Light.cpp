#include "Light.hpp"

Light::Light(glm::vec3 color, GLfloat aIntensity, GLfloat dIntensity)
    : m_color(color),
      m_ambientIntensity(aIntensity),
      m_diffuseIntensity(dIntensity) {}
