cmake_minimum_required(VERSION 3.0)
project(Falling-Elements)

find_package(OpenGL REQUIRED)

set (CMAKE_CXX_STANDARD 11)

# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

include_directories(
	external/glfw-3.3.8/include
	external/glm-0.9.9.8/
	external/glew-2.2.0/include
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_220
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_220
)

add_executable(Falling-Elements
	src/Instrumentor.h

	src/main.cpp
	src/Application.h
	src/Application.cpp
	src/ShaderProgram.h
	src/ShaderProgram.cpp

	src/Renderer/GridRenderer.h
	src/Renderer/GridRenderer.cpp

	src/UI/UserInterface.h
	src/UI/UserInterface.cpp
	src/UI/TextureLoader/TextureLoader.hpp
	src/UI/TextureLoader/TextureLoader.cpp

	src/InputManager/InputManager.h
	src/InputManager/InputManager.cpp
	src/InputManager/Brush/Brush.h
	src/InputManager/Brush/Brush.cpp
	src/InputManager/Brush/SquareBrush.h
	src/InputManager/Brush/SquareBrush.cpp
	src/InputManager/Brush/CircleBrush.h
	src/InputManager/Brush/CircleBrush.cpp

	src/Cell/Cell.h
	src/Cell/Cell.cpp
	src/Cell/MovementBehavior/IMovementBehavior.h
	src/Cell/MovementBehavior/IMovementBehavior.cpp
	src/Cell/MovementBehavior/SandBehavior.h
	src/Cell/MovementBehavior/SandBehavior.cpp
	src/Cell/MovementBehavior/WaterBehavior.h
	src/Cell/MovementBehavior/WaterBehavior.cpp
	src/Cell/MovementBehavior/StaticBehavior.h
	src/Cell/MovementBehavior/StaticBehavior.cpp
	src/Cell/MovementBehavior/ParticleBehavior.h
	src/Cell/MovementBehavior/ParticleBehavior.cpp
	src/Cell/MovementBehavior/SmokeBehavior.h
	src/Cell/MovementBehavior/SmokeBehavior.cpp
	src/Cell/MovementBehavior/RockBehavior.h
	src/Cell/MovementBehavior/RockBehavior.cpp
	src/Cell/MovementBehavior/GazBehavior.h
	src/Cell/MovementBehavior/GazBehavior.cpp

	src/Cell/ThermicBehavior/IThermicBehavior.h
	src/Cell/ThermicBehavior/IThermicBehavior.cpp
	src/Cell/ThermicBehavior/WaterThermic.h
	src/Cell/ThermicBehavior/WaterThermic.cpp
	src/Cell/ThermicBehavior/LavaThermic.h
	src/Cell/ThermicBehavior/LavaThermic.cpp
	src/Cell/ThermicBehavior/RockThermic.h
	src/Cell/ThermicBehavior/RockThermic.cpp
	src/Cell/ThermicBehavior/SteamThermic.h
	src/Cell/ThermicBehavior/SteamThermic.cpp
	src/Cell/ThermicBehavior/FlameThermic.h
	src/Cell/ThermicBehavior/FlameThermic.cpp
	src/Cell/ThermicBehavior/FlammableThermic.h
	src/Cell/ThermicBehavior/FlammableThermic.cpp

	src/Cell/Factory/CellFactory.h
	src/Cell/Factory/CellFactory.cpp

	# STB IMAGE
	src/vendor/stb/stb_image.h

	# IMGUI
	src/vendor/imgui/imconfig.h
	src/vendor/imgui/imgui.h
	src/vendor/imgui/imgui.cpp
	src/vendor/imgui/imgui_draw.cpp
	src/vendor/imgui/imgui_impl_glfw.cpp
	src/vendor/imgui/imgui_impl_glfw.h
	src/vendor/imgui/imgui_impl_opengl3.cpp
	src/vendor/imgui/imgui_impl_opengl3.h
	src/vendor/imgui/imgui_impl_opengl3_loader.h
	src/vendor/imgui/imgui_internal.h
	src/vendor/imgui/imgui_tables.cpp
	src/vendor/imgui/imgui_widgets.cpp

)
target_link_libraries(Falling-Elements
	${ALL_LIBS}
)
