#pragma once

#include "GameObject.hpp"
#include "Controller/LuaManager.hpp"

class ScriptableObject : public GameObject {
public:
	ScriptableObject(std::string script);

	void init(){};

	void update(float delta_time);

	void add_draw_call() {}

	void draw(std::shared_ptr<Shader> shader) {}

	~ScriptableObject(){};

private:
	std::string scriptPath;
};
