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
	const int WIN_WIDTH, WIN_HEIGHT, UI_WIDTH;

	int& _selectedElement;
	int& _selectedBrush;
	int& _selectedFilter;
	Cell** _hoveredCell;

	void updateElementSelection();
	void updateBrushSelection();
	void updateHoveredCellInfo();

public:
	UserInterface(const WindowData& windowData, int& selectedElement, int& selectedBrush, int& _selectedFilter, Cell** hoveredCell);

	void createNewFrame();
	void update();
	void render();
	void shutdown();

};
