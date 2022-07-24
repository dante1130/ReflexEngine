#include "Camera.hpp"
#include "Controller/LuaManager.hpp"

void Camera::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	auto movement_enum = lua.new_enum("Movement", "forward", Movement::forward,
	                                  "backward", Movement::backward, "left",
	                                  Movement::left, "right", Movement::right);

	auto camera_table = lua.create_named_table("Camera");

	camera_table.set_function("is_noclip", &Camera::is_noclip, this);
	camera_table.set_function("get_position", &Camera::get_position, this);
	camera_table.set_function("get_direction", &Camera::get_direction, this);
	camera_table.set_function("set_position", &Camera::set_position, this);
	camera_table.set_function("toggle_noclip", &Camera::toggle_noclip, this);
	camera_table.set_function("move", &Camera::move, this);
}

Camera::Camera() { Update(); }

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch,
               GLfloat move_speed, GLfloat turn_speed)
    : position_(position),
      front_(glm::vec3(0.0f, 0.0f, -1.0f)),
      up_(0.0f),
      right_(0.0f),
      up_world_(up),
      yaw_(yaw),
      pitch_(pitch),
      move_speed_(move_speed),
      turn_speed_(turn_speed)

{
	Update();
}

void Camera::move(Movement movement, GLfloat delta_time) {
	GLfloat velocity = move_speed_ * delta_time;

	glm::vec3 front;
	glm::vec3 right;

	if (is_noclip_) {
		front = front_;
		right = right_;
	} else {
		front = glm::normalize(glm::vec3(front_.x, 0.0f, front_.z));
		right = glm::normalize(glm::vec3(right_.x, 0.0f, right_.z));
	}

	switch (movement) {
		case Movement::forward:
			position_ += front * velocity;
			break;
		case Movement::backward:
			position_ -= front * velocity;
			break;
		case Movement::left:
			position_ -= right * velocity;
			break;
		case Movement::right:
			position_ += right * velocity;
			break;
	}
}

void Camera::calculate_direction(Movement movement) {
	glm::vec3 front;
	glm::vec3 right;

	if (is_noclip_) {
		front = front_;
		right = right_;
	} else {
		front = glm::normalize(glm::vec3(front_.x, 0.0f, front_.z));
		right = glm::normalize(glm::vec3(right_.x, 0.0f, right_.z));
	}

	switch (movement) {
		case Movement::forward:
			direction_ += front;
			break;
		case Movement::backward:
			direction_ -= front;
			break;
		case Movement::left:
			direction_ -= right;
			break;
		case Movement::right:
			direction_ += right;
			break;
		default:
			direction_ = glm::vec3(0.0f, 0.0f, 0.0f);
			break;
	}

	direction_ = glm::normalize(direction_);
}

void Camera::mouse_move(GLfloat x_offset, GLfloat y_offset) {
	x_offset *= turn_speed_;
	y_offset *= turn_speed_;

	yaw_ += x_offset;
	pitch_ += y_offset;

	pitch_ = glm::clamp(pitch_, -89.0f, 89.0f);

	Update();
}

glm::mat4 Camera::calc_view_matrix() {
	return glm::lookAt(position_, position_ + front_, up_);
}

void Camera::set_position(glm::vec3 position) { position_ = position; }

void Camera::set_move_direction(glm::vec3 direction) { direction_ = direction; }

void Camera::Update() {
	front_.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front_.y = sin(glm::radians(pitch_));
	front_.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));

	front_ = glm::normalize(front_);

	right_ = glm::normalize(glm::cross(front_, up_world_));
	up_ = glm::normalize(glm::cross(right_, front_));
}

glm::vec3 Camera::get_position() const { return position_; }

glm::vec3 Camera::get_direction() const { return glm::normalize(front_); }

glm::vec3 Camera::get_move_direction() const { return direction_; }

glm::vec3 Camera::get_up_world() const { return up_world_; }

bool Camera::is_noclip() const { return is_noclip_; }

void Camera::toggle_noclip() { is_noclip_ = !is_noclip_; }

float Camera::cam_pos_x() { return position_.x; }
float Camera::cam_pos_y() { return position_.y; }
float Camera::cam_pos_z() { return position_.z; }
float Camera::cam_look_x() { return get_direction().x; }
float Camera::cam_look_y() { return get_direction().y; }
float Camera::cam_look_z() { return get_direction().z; }

void Camera::set_move_dir_x(float x) { direction_.x = x; }
void Camera::set_move_dir_y(float y) { direction_.y = y; }
void Camera::set_move_dir_z(float z) { direction_.z = z; }
