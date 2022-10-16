#include "UserInterface.h"

UserInterface::UserInterface(const WindowData& windowData, int& selectedElement, int& selectedBrush, int& selectedFilter, Cell** hoveredCell)
	: _window(windowData.window), WIN_WIDTH(windowData.WIN_WIDTH), WIN_HEIGHT(windowData.WIN_HEIGHT),
		_selectedElement(selectedElement), _selectedBrush(selectedBrush), _selectedFilter(selectedFilter),
		_hoveredCell(hoveredCell)
{
#if defined(IMGUI_IMPL_OPENGL_ES2)
	const char* glsl_version = "#version 100";
#elif defined(__APPLE__)
	const char* glsl_version = "#version 150";
#else
	const char* glsl_version = "#version 130";
#endif
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags = 1 << 5; // Prevent ImGui to draw cursor
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(&_window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void UserInterface::createNewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UserInterface::update()
{
	const int PANNEL_WIDTH = WIN_WIDTH * 0.2f; // 20% of window width
	const int PANNEL_HEIGHT = WIN_HEIGHT;

	ImGui::SetNextWindowPos(ImVec2(WIN_WIDTH - PANNEL_WIDTH, 0.0f));
	ImGui::SetNextWindowSize(ImVec2(PANNEL_WIDTH, PANNEL_HEIGHT));

	ImGuiWindowFlags windowFlag = 0;
	windowFlag |= ImGuiWindowFlags_NoMove;
	windowFlag |= ImGuiWindowFlags_NoResize;
	windowFlag |= ImGuiWindowFlags_NoCollapse;

	ImGui::Begin("Main Tab");

	updateElementSelection();
	updateBrushSelection();
	ImGui::Combo("Filter", &_selectedFilter, "Normal\0Velocity\0Temperature\0");
	updateHoveredCellInfo();

	ImGui::End();
}

void UserInterface::updateElementSelection()
{
	ImGui::Text("Element selection");
	for (int i = 0; i < 8; i++)
	{
		char text[32];
		snprintf(text, 32, "Element %d", i);
		if (ImGui::Selectable(text, _selectedElement == i))
			_selectedElement = i;
	}
}

void UserInterface::updateBrushSelection()
{
	ImGui::Text("\nBrush selection");
	
	int newBrushSize = Brush::brushSize;
	ImGui::SliderInt("Brush size", &newBrushSize, 1, 64);
	if (newBrushSize != Brush::brushSize)
	{
		Brush::brushSize = newBrushSize;
		Brush::updateCursor(_selectedBrush, &_window);
	}

	if (ImGui::Selectable("Square brush", _selectedBrush == 0))
	{
		_selectedBrush = 0;
		Brush::updateCursor(0, &_window);
	}
	if (ImGui::Selectable("Circle brush", _selectedBrush == 1))
	{
		_selectedBrush = 1;
		Brush::updateCursor(1, &_window);
	}
}

void UserInterface::updateHoveredCellInfo()
{
	if (*_hoveredCell != nullptr)
	{
		Cell& cell = **_hoveredCell;
		ImGui::Text("Position: %d %d", (int)cell.getPosition().x, (int)cell.getPosition().y);
		ImGui::Text("Temperature: %lf", cell._temperature);
	}
}

void UserInterface::render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UserInterface::shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
