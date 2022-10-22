#include "UserInterface.h"

UserInterface::UserInterface(const WindowData& windowData, int& selectedElement, int& selectedBrush, int& selectedFilter, Cell** hoveredCell)
	: _window(windowData.window), WIN_WIDTH(windowData.WIN_WIDTH), WIN_HEIGHT(windowData.WIN_HEIGHT), UI_WIDTH(windowData.UI_WIDTH),
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

	// Textures init
	_textures.push_back(TextureLoader("textures/test.png"));
	_textures.push_back(TextureLoader("textures/test1.png"));
}

void UserInterface::createNewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UserInterface::update()
{
	const int PANNEL_WIDTH = UI_WIDTH; 
	const int PANNEL_HEIGHT = WIN_HEIGHT;

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowBorderSize = 0;

	ImGui::SetNextWindowPos(ImVec2(WIN_WIDTH - PANNEL_WIDTH, 0.0f));
	ImGui::SetNextWindowSize(ImVec2(PANNEL_WIDTH, PANNEL_HEIGHT));

	ImGuiWindowFlags windowFlag = 0;
	windowFlag |= ImGuiWindowFlags_NoMove;
	windowFlag |= ImGuiWindowFlags_NoResize;
	windowFlag |= ImGuiWindowFlags_NoCollapse;
	windowFlag |= ImGuiWindowFlags_NoTitleBar;

	ImGui::Begin("Menu", NULL, windowFlag);

	updateFiltersSelection();
	updateElementSelection();
	updateBrushSelection();
	//ImGui::Combo("Filter", &_selectedFilter, "Normal\0Velocity\0Temperature\0");
	updateHoveredCellInfo();

	ImGui::End();
}

void UserInterface::updateFiltersSelection()
{
	ImGui::BeginChild("Filters", ImVec2(UI_WIDTH, 50));
	ImGui::Text("Filters section");
	ImGui::EndChild();
	ImGui::Separator();
}

void UserInterface::updateElementSelection()
{
	ImGui::BeginChild("Elements", ImVec2(UI_WIDTH, 200));
	ImGui::Text("Element selection");
	for (int i = 0; i < 8; i++)
	{
		char text[32];
		snprintf(text, 32, "Element %d", i);
		if (ImGui::Selectable(text, _selectedElement == i))
			_selectedElement = i;
	}
	ImGui::EndChild();
	ImGui::Separator();
}

void UserInterface::updateBrushSelection()
{
	ImGuiIO& io = ImGui::GetIO();

	ImGui::BeginChild("Brushes", ImVec2(UI_WIDTH, 150));
	ImGui::Text("\nBrush selection");
	
	int newBrushSize = Brush::brushSize;
	ImGui::SliderInt("Brush size", &newBrushSize, 1, 64);
	if (newBrushSize != Brush::brushSize)
	{
		Brush::brushSize = newBrushSize;
		Brush::updateCursor(_selectedBrush, &_window);
	}

	//if (ImGui::Selectable("Square brush", _selectedBrush == 0))
	if (ImGui::ImageButton((void*)(intptr_t)_textures[0].getTexture(), ImVec2(32.0f, 32.0f)) == 0);
	{
		std::cout << "SQUARE" << std::endl;
		_selectedBrush = 0;
		Brush::updateCursor(0, &_window);
	}
	ImGui::SameLine();
	if (ImGui::ImageButton((void*)(intptr_t)_textures[1].getTexture(), ImVec2(32.0f, 32.0f)) == 0);
	{
		std::cout << "CIRCLE" << std::endl;
		_selectedBrush = 1;
		Brush::updateCursor(1, &_window);
	}
	ImGui::EndChild();
	ImGui::Separator();
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
