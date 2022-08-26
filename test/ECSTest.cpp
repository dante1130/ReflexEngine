#include <catch2/catch_test_macros.hpp>

#include "Controller/ECS/ECS.hpp"
#include "Controller/ECS/Entity.hpp"
#include "Model/Components/Transform.hpp"

TEST_CASE("Entity tests", "[ECS]") {
	ECS ecs;

	SECTION("Creating an entity") {
		auto& entity = ecs.create_entity("test");

		auto entity_id = entity.get_entity_id();

		REQUIRE(entity.get_name() == "test");
		REQUIRE(ecs.get_registry().valid(entity_id));

		ecs.destroy_entity(entity_id);
	}

	SECTION("Destroying an entity") {
		auto& entity = ecs.create_entity("test");

		auto entity_id = entity.get_entity_id();
		ecs.destroy_entity(entity_id);

		REQUIRE(!ecs.get_registry().valid(entity_id));
	}

	SECTION("Clearing entites from ECS") {
		constexpr size_t entity_count = 100;

		std::vector<entt::entity> entities_id_vec;
		entities_id_vec.reserve(entity_count);

		for (size_t i = 0; i < entity_count; ++i) {
			entities_id_vec.emplace_back(
			    ecs.create_entity(std::to_string(i)).get_entity_id());
		}

		ecs.clear_entities();

		bool is_any_valid_entities =
		    std::any_of(entities_id_vec.begin(), entities_id_vec.end(),
		                [&ecs](entt::entity entity_id) {
			                return ecs.get_registry().valid(entity_id);
		                });

		REQUIRE(!is_any_valid_entities);
	}

	SECTION("Adding components to an entity") {
		auto& entity = ecs.create_entity("test");
		entity.add_component<int>(1);
		entity.add_component<float>(1.0f);
		entity.add_component<double>(1.0);
		entity.add_component<std::string>("test");
		entity.add_component<bool>(true);
		entity.add_component<Component::Transform>();

		REQUIRE(entity.any_component<int>());
		REQUIRE(entity.any_component<float>());
		REQUIRE(entity.any_component<double>());
		REQUIRE(entity.any_component<std::string>());
		REQUIRE(entity.any_component<bool>());
		REQUIRE(entity.any_component<Component::Transform>());

		ecs.destroy_entity(entity.get_entity_id());
	}

	SECTION("Removing components from an entity") {
		auto& entity = ecs.create_entity("test");
		entity.add_component<int>(1);
		entity.add_component<float>(1.0f);
		entity.add_component<double>(1.0);
		entity.add_component<std::string>("test");
		entity.add_component<bool>(true);
		entity.add_component<Component::Transform>();

		entity.remove_component<int>();
		entity.remove_component<float>();
		entity.remove_component<double>();
		entity.remove_component<std::string>();
		entity.remove_component<bool>();
		entity.remove_component<Component::Transform>();

		REQUIRE(!entity.any_component<int>());
		REQUIRE(!entity.any_component<float>());
		REQUIRE(!entity.any_component<double>());
		REQUIRE(!entity.any_component<std::string>());
		REQUIRE(!entity.any_component<bool>());
		REQUIRE(!entity.any_component<Component::Transform>());

		ecs.destroy_entity(entity.get_entity_id());
	}
}
