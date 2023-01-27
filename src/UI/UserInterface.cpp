#include "UserInterface.h"

UserInterface::UserInterface(const WindowData& windowData, const SimulationData& simulationData, const CellsArrayData& cellsArrayData)
	: _window(windowData.window), WIN_WIDTH(windowData.WIN_WIDTH), WIN_HEIGHT(windowData.WIN_HEIGHT), UI_WIDTH(windowData.UI_WIDTH),
		_selectedElement(simulationData.selectedElement), _selectedBrush(simulationData.selectedBrush), _selectedFilter(simulationData.selectedFilter),
		_hoveredCell(simulationData.hoveredCell), _simulationSpeed(simulationData.simulationSpeed), _cells(cellsArrayData.cells),
		CELL_HEIGHT(cellsArrayData.CELL_HEIGHT), CELL_WIDTH(cellsArrayData.CELL_WIDTH)
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
	std::string path = "./"; // Linux and MacOs path

	try {
		_textures.push_back(TextureLoader(path + "textures/square.png"));
	}
	catch (std::invalid_argument&) {
		path = "../../../"; // Windows path
	}

	try {
		if (_textures.size() == 0)
			_textures.push_back(TextureLoader(path + "textures/square.png"));
		_textures.push_back(TextureLoader(path + "textures/circle.png"));
		_textures.push_back(TextureLoader(path + "textures/air.png"));
		_textures.push_back(TextureLoader(path + "textures/sand.png"));
		_textures.push_back(TextureLoader(path + "textures/water.png"));
		_textures.push_back(TextureLoader(path + "textures/stone.png"));
		_textures.push_back(TextureLoader(path + "textures/steam.png"));
		_textures.push_back(TextureLoader(path + "textures/lava.png"));
		_textures.push_back(TextureLoader(path + "textures/oil.png"));
		_textures.push_back(TextureLoader(path + "textures/fire.png"));
		_textures.push_back(TextureLoader(path + "textures/ice.png"));
		_textures.push_back(TextureLoader(path + "textures/steel.png"));
		_textures.push_back(TextureLoader(path + "textures/co2.png"));
	}
	catch (std::invalid_argument&) {
		std::cerr << "Cannot open ui textures" << std::endl;
		exit(1);
	}
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
	updateHoveredCellInfo();

	ImGui::End();
}

void UserInterface::updateFiltersSelection()
{
	ImGui::BeginChild("Filters", ImVec2(UI_WIDTH, 50));
	ImGui::Text("Filters section");
	ImGui::Combo("Filter", &_selectedFilter, "Normal\0Velocity\0Temperature\0");
	ImGui::EndChild();
	ImGui::Separator();
}

void UserInterface::updateElementSelection()
{
	const int ELEMENTS_NUMBER = 11;
	const int ELEMENTS_PER_LINE = 6;
	const char* ELEMENTS_NAMES[] {
		"Air", "Sand", "Water", "Stone", "Steam", "Lava", "Oil", "Fire", "Ice", "Steel", "Co2"
	};

	ImGui::BeginChild("Elements", ImVec2(UI_WIDTH, 200));
	ImGui::Text("Element selection");
	for (int i = 0; i < ELEMENTS_NUMBER; i++)
	{
		ImVec2 size = ImVec2(32.0f, 32.0f);
		ImVec2 uv0 = ImVec2(0.0f, 0.0f);
		ImVec2 uv1 = ImVec2(1.0f, 1.0f);
		ImVec4 bg_col;
		ImVec4 tint_col;
		if (_selectedElement == i)
		{
			tint_col = ImVec4(ImVec4(0.6f, 0.6f, 0.6f, 0.6f));
			bg_col = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
		}
		else
		{
			tint_col = ImVec4(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
			bg_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		}

		bool imageReturn = (ImGui::ImageButton((void*)(intptr_t)_textures[i+2].getTexture(), size, uv0, uv1, 3, bg_col, tint_col));
		if (imageReturn)
			_selectedElement = i;

		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(ELEMENTS_NAMES[i]);

		if (i % ELEMENTS_PER_LINE != ELEMENTS_PER_LINE - 1)
			ImGui::SameLine();
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

	for (int i = 0; i < 2; i++)
	{
		ImVec2 size = ImVec2(32.0f, 32.0f);
		ImVec2 uv0 = ImVec2(0.0f, 0.0f);
		ImVec2 uv1 = ImVec2(1.0f, 1.0f);
		ImVec4 bg_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ImVec4 tint_col;
		if (_selectedBrush == i)
			tint_col = ImVec4(ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
		else
			tint_col = ImVec4(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

		bool imageReturn = (ImGui::ImageButton((void*)(intptr_t)_textures[i].getTexture(), size, uv0, uv1, -1, bg_col, tint_col));
		if (imageReturn)
		{
			_selectedBrush = i;
			Brush::updateCursor(i, &_window);
		}

		if (i < 2)
			ImGui::SameLine();
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
	ImGui::NewLine();
	ImGui::Text("Targeted updates per second");

	int frameRateTarget = (int)(1.0f / _simulationSpeed);
	int sliderValue = frameRateTarget;
	ImGui::SliderInt("ups", &sliderValue, 1, 120);
	if (sliderValue != frameRateTarget)
		_simulationSpeed = 1.0f / (float)sliderValue;

	double sum = 0;
	for (int y = 0; y < CELL_HEIGHT; y++)
		for (int x = 0; x < CELL_WIDTH; x++)
			sum += _cells[y][x]._temperature;
	sum /= (CELL_HEIGHT * CELL_WIDTH);
	ImGui::Text("Mean temperature: %f", sum);
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
