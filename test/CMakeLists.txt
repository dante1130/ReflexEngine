target_sources(ReflexEngineTest PRIVATE
	ShaderTest.cpp
	ECSTest.cpp
	CollectionsTest.cpp
	PerformanceLoggerTest.cpp
	PhysicsTest.cpp
	AffordanceTest.cpp
)

target_include_directories(ReflexEngineTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(ReflexEngineTest SYSTEM ${CMAKE_PREFIX_PATH}/catch2/src)
