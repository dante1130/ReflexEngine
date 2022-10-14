#include <glm/glm.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

/**
 * @author Daniel Rodic
 * @brief Outputs collision resolution data, mainly in MATLAB output
 */
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

/**
 * @brief Outputs the before data of body 1 in collision
 *
 * @param mass the mass of the body
 * @param vel the velocity of the body
 * @param angVel the angular velocity of the body (in world coordiantes)
 * @param collision_point the collision point
 * @param i_r_it the inverse of the rotated inertia tensor
 * @param it the inertia tensor
 * @param orientation the orientation of the body
 */
auto output_before_resolution_b1(float mass, glm::vec3 vel, glm::vec3 angVel,
                                 glm::vec3 collision_point, glm::mat3x3 i_r_it,
                                 glm::mat3x3 it, glm::quat orientation) -> void;

/**
 * @brief Outputs the before data of body 2 in collision
 *
 * @param mass the mass of the body
 * @param vel the velocity of the body
 * @param angVel the angular velocity of the body (in world coordiantes)
 * @param collision_point the collision point
 * @param i_r_it the inverse of the rotated inertia tensor
 * @param it the inertia tensor
 * @param orientation the orientation of the body
 */
auto output_before_resolution_b2(float mass, glm::vec3 vel, glm::vec3 angVel,
                                 glm::vec3 collision_point, glm::mat3x3 i_r_it,
                                 glm::mat3x3 it, glm::quat orientation) -> void;

/**
 * @brief Outputs the new velocities after running a collision resolution
 * method
 *
 * @param b1_vel the velocity of the first collision body
 * @param b1_angVel the angular velocity of the first collision body
 * @param b2_vel the velocity of the second collision body
 * @param b2_angVel the angular velocity of the second collision body
 */
auto output_after_resolution(glm::vec3 b1_vel, glm::vec3 b1_angVel,
                             glm::vec3 b2_vel, glm::vec3 b2_angVel) -> void;
}  // namespace ResolutionOutput