#include "ResolutionOutput.hpp"

#include <iostream>
#include <string>

auto ResolutionOutput::output_resolution_data(float epsilon, float lambda,
                                              glm::vec3 collision_normal,
                                              glm::vec3 numerator,
                                              glm::vec3 denominator) -> void {
	glm::vec3 linear_impulse = lambda * collision_normal;

	std::cout.setf(std::ios::fixed);
	std::cout << "\n\nGeneral Info\n"
	          << "Epsilon = " << epsilon << "\ncollision_normal = ["
	          << collision_normal.x << "; " << collision_normal.y << "; "
	          << collision_normal.z << "];"
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

auto ResolutionOutput::output_before_resolution_b1(
    float mass, glm::vec3 vel, glm::vec3 angVel, glm::vec3 collision_point,
    glm::mat3x3 i_r_it, glm::mat3x3 it, glm::quat orientation) -> void {
	std::cout.setf(std::ios::fixed);
	std::cout << "\n\n%-----Object 1 - Before Collision"
	          << "\nb1_mass = " << mass << "\nb1_vel = [" << vel.x << "; "
	          << vel.y << "; " << vel.z << "];"
	          << "\nb1_angVel = [" << angVel.x << "; " << angVel.y << "; "
	          << angVel.z << "];"
	          << "\nc1_dist = [" << collision_point.x << "; "
	          << collision_point.y << "; " << collision_point.z << "];"
	          << "\nb1_inertia_tensor = [" << i_r_it[0][0] << " "
	          << i_r_it[1][0] << " " << i_r_it[2][0] << "; " << i_r_it[0][1]
	          << " " << i_r_it[1][1] << " " << i_r_it[2][1] << "; "
	          << i_r_it[0][2] << " " << i_r_it[1][2] << " " << i_r_it[2][2]
	          << "];"
	          << "\nb1_it = [" << it[0][0] << " " << it[1][0] << " " << it[2][0]
	          << "; " << it[0][1] << " " << it[1][1] << " " << it[2][1] << "; "
	          << it[0][2] << " " << it[1][2] << " " << it[2][2] << "];"
	          << "\n%orientation (w,x,y,z) = " << orientation.w << " "
	          << orientation.x << " " << orientation.y << " " << orientation.z
	          << std::endl;
}

auto ResolutionOutput::output_before_resolution_b2(
    float mass, glm::vec3 vel, glm::vec3 angVel, glm::vec3 collision_point,
    glm::mat3x3 i_r_it, glm::mat3x3 it, glm::quat orientation) -> void {
	std::cout.setf(std::ios::fixed);
	std::cout << "%-----Object 2 - Before Collision"
	          << "\nb2_mass = " << mass << "\nb2_vel = [" << vel.x << "; "
	          << vel.y << "; " << vel.z << "];"
	          << "\nb2_angVel = [" << angVel.x << "; " << angVel.y << "; "
	          << angVel.z << "];" << collision_point.y << "; "
	          << collision_point.z << "];"
	          << "\nb2_inertia_tensor = [" << i_r_it[0][0] << " "
	          << i_r_it[1][0] << " " << i_r_it[2][0] << "; " << i_r_it[0][1]
	          << " " << i_r_it[1][1] << " " << i_r_it[2][1] << "; "
	          << i_r_it[0][2] << " " << i_r_it[1][2] << " " << i_r_it[2][2]
	          << "];"
	          << "\nb2_it = [" << it[0][0] << " " << it[1][0] << " " << it[2][0]
	          << "; " << it[0][1] << " " << it[1][1] << " " << it[2][1] << "; "
	          << it[0][2] << " " << it[1][2] << " " << it[2][2] << "];"
	          << "\n%orientation (w,x,y,z) = " << orientation.w << " "
	          << orientation.x << " " << orientation.y << " " << orientation.z
	          << std::endl;
}

auto ResolutionOutput::output_after_resolution(glm::vec3 b1_vel,
                                               glm::vec3 b1_angVel,
                                               glm::vec3 b2_vel,
                                               glm::vec3 b2_angVel) -> void {
	std::cout.setf(std::ios::fixed);
	std::cout << "\n%Object 1 - After Collision"
	          << "\nnew_b1_Vel = [" << b1_vel.x << " " << b1_vel.y << " "
	          << b1_vel.z << "];"
	          << "\nnew_b1_angVel = [" << b1_angVel.x << " " << b1_angVel.y
	          << " " << b1_angVel.z << "];"
	          << "\n%Object 2 - After Collision"
	          << "\nnew_b2_Vel = [" << b2_vel.x << " " << b2_vel.y << " "
	          << b2_vel.z << "];"
	          << "\nnew_b2_angVel = [" << b2_angVel.x << " " << b2_angVel.y
	          << " " << b2_angVel.z << "];" << std::endl;
}