#include "Water.hpp"
#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/ResourceManager/ResourceManager.hpp"
Water::Water(std::string filePath) {
	m_texture = Texture(filePath.c_str());
	m_texture.LoadTexture();
	init();
}

Water::Water(Texture &text) {
	m_texture = text;
	init();
}

Water::Water(Texture &text, glm::vec3 pos, glm::vec3 scale, glm::vec3 offMult) {
	m_time = 0;
	position = pos;
	setIntensity(scale);
	m_offsetMult = offMult;

	m_texture = text;
	init();
}

void Water::init() {
	float verts[] = {-10.0f, 0.0f,  -10.0f, 0.0f,   0.0f,   0.0f,  -1.0f, 0.0f,
							10.0f, 0.0f,   -10.0f, 100.0f, 0.0f,  0.0f, -1.0f,   0.0f,
							-10.0f, 0.0f,   10.0f,  0.0f,  100.0f, 0.0f,   -1.0f,  0.0f, 
							10.0f,  0.0f,   10.0f, 100.0f, 100.0f, 0.0f,  -1.0f,   0.0f};
	const uint32_t order[6] = {0u, 2u, 1u, 1u, 2u, 3u};

	m_mesh.CreateMesh(verts, order, 32, 6);

	verts[6] = 1.0f;
	verts[14] = 1.0f;
	verts[22] = 1.0f;
	verts[30] = 1.0f;
	const uint32_t orderTwo[6] = {0u, 1u, 2u, 1u, 3u, 2u};
	m_mesh_under.CreateMesh(verts, orderTwo, 32, 6);
}

void Water::update(float delta_time) {
	m_time += delta_time;

	float x = sin(m_time * m_offsetMult.x) / m_intensity.x;
	float y = sin(m_time * m_offsetMult.y) / m_intensity.y;
	float z = sin(m_time * m_offsetMult.z) / m_intensity.z;

	m_pos.x = position.x + x;
	m_pos.y = position.y + y;
	m_pos.z = position.z + z;
}

void Water::add_draw_call() {
	DrawCall draw_call = [=](std::shared_ptr<Shader> shader) { draw(shader); };

	ReflexEngine::get_instance().renderer_.add_draw_call(draw_call);
}

void Water::draw(std::shared_ptr<Shader> shader) {
	auto default_shader = ReflexEngine::get_instance().renderer_.get_shader();

	glm::mat4 model(1.0f);
	model = glm::translate(model, m_pos);

	model = glm::scale(model, glm::vec3(100, 1, 100));

	glUniformMatrix4fv(shader->GetModelLocation(), 1, GL_FALSE,
	                   glm::value_ptr(model));
	glUniform1i(shader->GetUsingTexture(), true);
	// m_texture.UseTexture();
	TextureManager &tm = ResourceManager::get_instance().get_texture_manager();
	const Texture &t = tm.get_texture("water");
	t.UseTexture();

	m_mesh.RenderMesh();
	m_mesh_under.RenderMesh();
}

void Water::setIntensity(glm::vec3 scale) {
	m_intensity = scale;
	if (m_intensity.x == 0) {
		m_intensity.x = 1;
	}
	if (m_intensity.y == 0) {
		m_intensity.y = 1;
	}
	if (m_intensity.z == 0) {
		m_intensity.z = 1;
	}
}

void Water::setOffsetMult(glm::vec3 offMult) { m_offsetMult = offMult; }
