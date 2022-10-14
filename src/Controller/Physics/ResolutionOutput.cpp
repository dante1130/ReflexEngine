#include "ResolutionOutput.hpp"

#include <iostream>
#include <string>

auto ResolutionOutput::output_resolution_data(float epsilon, float lambda,
                                              glm::vec3 collision_normal,
                                              glm::vec3 numerator,
                                              glm::vec3 denominator) -> void {
	glm::vec3 linear_impulse = lambda * collision_normal;

	std::cout << "\n\nGeneral Info\n"
	          << "Epsilon = " << epsilon << "\ncollision_normal = ["
	          << std::to_string(collision_normal.x) << "; "
	          << std::to_string(collision_normal.y) << "; "
	          << std::to_string(collision_normal.z) << "];"
	          << "\nvel_num_eqn = " << numerator.x
	          << "\nw1_num_eqn = " << numerator.y
	          << "\nw2_num_eqn = " << numerator.z << "\nnum_eqn = "
	          << -(1 + epsilon) * (numerator.x + numerator.y - numerator.z)
	          << "\nmass_div_eqn = " << denominator.x
	          << "\nj1_div_eqn = " << denominator.y
	          << "\nj2_div_eqn = " << denominator.z
	          << "\ndiv_eqn = " << numerator.x + (numerator.y + numerator.z)
	          << "\nLambda = " << lambda
	          << "\nLinear impluse = " << linear_impulse.x << " "
	          << linear_impulse.y << " " << linear_impulse.z << std::endl;
}

auto ResolutionOutput::output_before_resolution() -> void {}

auto ResolutionOutput::output_after_resolution(glm::vec3 b1_vel,
                                               glm::vec3 b1_angVel,
                                               glm::vec3 b2_vel,
                                               glm::vec3 b2_angVel) -> void {
	std::cout << "\n%Object 1 - After Collision"
	          << "\nnew_b1_Vel = [" << std::to_string(b1_vel.x) << " "
	          << std::to_string(b1_vel.y) << " " << std::to_string(b1_vel.z)
	          << "];"
	          << "\nnew_b1_angVel = [" << std::to_string(b1_angVel.x) << " "
	          << std::to_string(b1_angVel.y) << " "
	          << std::to_string(b1_angVel.z) << "];"
	          << "%Object 2 - After Collision"
	          << "\nnew_b2_Vel = [" << std::to_string(b2_vel.x) << " "
	          << std::to_string(b2_vel.y) << " " << std::to_string(b2_vel.z)
	          << "];"
	          << "\nnew_b2_angVel = [" << std::to_string(b2_angVel.x) << " "
	          << std::to_string(b2_angVel.y) << " "
	          << std::to_string(b2_angVel.z) << "];" << std::endl;
}