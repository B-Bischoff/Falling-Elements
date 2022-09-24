#pragma once

// OPENGL LIBRARY
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// IMGUI LIBRARY
#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

#include <cstdio>

#include "../Application.h"
#include "../Cell/Factory/CellFactory.h"

struct WindowData;

class UserInterface {
private:
	GLFWwindow& _window;
	const int WIN_WIDTH, WIN_HEIGHT;

	int& _selectedElement;

public:
	UserInterface(const WindowData& windowData, int& selectedElement);

	void createNewFrame();
	void update();
	void render();
	void shutdown();

};
