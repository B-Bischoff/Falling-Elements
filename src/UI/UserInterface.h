#pragma once

// OPENGL LIBRARY
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// IMGUI LIBRARY
#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

#include <cstdio>
#include <vector>

#include "../Application.h"
#include "../Cell/Factory/CellFactory.h"
#include "TextureLoader/TextureLoader.hpp"

struct WindowData;
struct SimulationData;
struct CellsArrayData;
class TextureLoader;

class UserInterface {
private:
	GLFWwindow& _window;
	const int WIN_WIDTH, WIN_HEIGHT, UI_WIDTH;
	const int CELL_HEIGHT, CELL_WIDTH;

	int& _selectedElement;
	int& _selectedBrush;
	int& _selectedFilter;
	float& _simulationSpeed;
	Cell** _hoveredCell;
	Cell** _cells;

	std::vector<TextureLoader> _textures;

	void updateFiltersSelection();
	void updateElementSelection();
	void updateBrushSelection();
	void updateHoveredCellInfo();

public:
	UserInterface(const WindowData& widowData, const SimulationData& simulationData, const CellsArrayData& cellArrayData);

	void createNewFrame();
	void update();
	void render();
	void shutdown();

};
