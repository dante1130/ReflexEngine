#include <glm/glm.hpp>

namespace ResolutionOutput {
/**
 * @brief Outputs the values calculated in the collision resolution method
 *
 * @param epsilon the coefficient of restitution
 * @param lambda the lambda for the transfer of momentum equation
 * @param collision_normal the collision normal of the collision
 * @param numerator the numerator of the transfer of momentum equation. x is
 * vel, y is angular of body 1, z is angular of body 2
 * @param denominator the denominator of the transfer of monentum equation. x is
 * mass, y is j1, z is j2
 */
auto output_resolution_data(float epsilon, float lambda,
                            glm::vec3 collision_normal, glm::vec3 numerator,
                            glm::vec3 denominator) -> void;

auto output_before_resolution() -> void;

/**
 * @brief Outputs the new velocities after running a collision resolution method
 *
 * @param b1_vel the velocity of the first collision body
 * @param b1_angVel the angular velocity of the first collision body
 * @param b2_vel the velocity of the second collision body
 * @param b2_angVel the angular velocity of the second collision body
 */
auto output_after_resolution(glm::vec3 b1_vel, glm::vec3 b1_angVel,
                             glm::vec3 b2_vel, glm::vec3 b2_angVel) -> void;
}  // namespace ResolutionOutput