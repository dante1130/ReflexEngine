#include "ECSScene.hpp"

#include "Controller/ECS/ECSAccess.hpp"

void ECSScene::init() { ECSAccess::register_ecs(); }

void ECSScene::add_game_object(const std::string& luaScript) {}

void ECSScene::mouse_controls(double xpos, double ypos) {}

void ECSScene::update(double delta_time) { ecs_.update(delta_time); }

void ECSScene::fixed_update(double delta_time) {
	ecs_.fixed_update(delta_time);
}

void ECSScene::add_draw_call() { ecs_.draw(); }

void ECSScene::save_game_objects() {}

void ECSScene::load_saved_game_objects() {}

void ECSScene::garbage_collection() {}