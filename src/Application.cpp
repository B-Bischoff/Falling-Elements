#include "Application.h"

Application::Application(const int& width, const int& height)
	: WIN_WIDTH(width), WIN_HEIGHT(height), _hoveredCell(nullptr)
{
	// GLFW init
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW." << std::endl;
		std::cin.get();
		exit(1);
	}
	// Window init
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	_window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Falling-Elements", NULL, NULL);
	if (_window == nullptr)
	{
		std::cerr << "Failed to initialize GLFW window." << std::endl;
		std::cin.get();
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(_window);

	// GLEW init
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW." << std::endl;
		std::cin.get();
		glfwTerminate();
		exit(1);
	}

	loop();
}

void Application::generateRandomSets()
{
	_randomSets = nullptr;
	_randomSets = new std::vector<int>[RANDOM_SETS_NB];
	if (_randomSets == nullptr)
	{
		std::cerr << "Failed to random sets." << std::endl;
		std::cin.get();
		exit(1);
	}

	// Fill all random sets with numbers from 0 to cell_width - 1
	for (int i = 0; i < CELL_WIDTH; i++)
		for (int j = 0; j < RANDOM_SETS_NB; j++)
			_randomSets[j].push_back(i);

	// Shuffle numbers in sets
	auto rng = std::default_random_engine {};
	for (int i = 0; i < RANDOM_SETS_NB; i++)
		std::shuffle(_randomSets[i].begin(), _randomSets[i].end(), rng);
}

void Application::loop()
{
	_simulationSpeed = 0.01666; // ~ 60 Fps
	_selectedElement = 1; // Sand by default
	_selectedBrush = 0; // Square brush by default
	_selectedFilter = 0;
	_currentRandomSet = 0;

	_cells = new Cell* [CELL_HEIGHT];
	if (_cells == nullptr)
		exit (1);
	for (int y = 0; y < CELL_HEIGHT; y++)
	{
		_cells[y] = new Cell [CELL_WIDTH];
		if (_cells[y] == nullptr)
			exit (1);
		for (int x = 0; x < CELL_WIDTH; x++)
		{
			Cell& cell = _cells[y][x];
			cell.setPosition(glm::vec2(x, y));
			cell.setCells(_cells);
			cell.setWidth(CELL_WIDTH);
			cell.setHeight(CELL_HEIGHT);
			CellFactory::configureAirCell(cell);
		}
	}

	WindowData windowData {
		*_window,
		WIN_WIDTH,
		WIN_HEIGHT,
		UI_WIDTH
	};
	CellsArrayData cellsArrayData {
		CELL_SIZE,
		CELL_WIDTH,
		CELL_HEIGHT,
		_cells
	};
	SimulationData simulationData {
		_selectedElement,
		_selectedBrush,
		_selectedFilter,
		_simulationSpeed,
		&_hoveredCell
	};

	InputManager input(windowData, cellsArrayData, simulationData);

	// Testing file opening depending on the OS
	std::string path = "./"; // Linux and MacOs path
	std::ifstream ifs;
	ifs.open(path + "src/shaders/shader.vert");
	if (!ifs.is_open())
	{
		path = "../../../";
		ifs.open(path + "src/shaders/shader.vert");
		if (!ifs.is_open())
		{
			std::cerr << "Cannot find shaders" << std::endl;
			exit(1);
		}
	}
	ifs.close();

	ShaderProgram program(path + "src/shaders/shader.vert", path + "src/shaders/shader.frag");
	GridRenderer renderer(cellsArrayData, windowData, _selectedFilter);
	UserInterface ui(windowData, simulationData, cellsArrayData);
	Brush::updateCursor(_selectedBrush, _window);
	generateRandomSets();

	double previousTime = glfwGetTime();
	double cycleTime = glfwGetTime();
	int frameCount = 0;

	while (!glfwWindowShouldClose(_window) && glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ui.createNewFrame();

		frameCount++;
		double currentTime = glfwGetTime();

		input.update();

		// Update cells
		const size_t totalCells = CELL_HEIGHT * CELL_WIDTH;
		if (currentTime - cycleTime >= _simulationSpeed)
		{
			size_t cellsUpdated = 0;
			while (cellsUpdated < totalCells)
			{
				for (int y = 0; y < CELL_HEIGHT; y++)
				{
					for (int x = 0; x < CELL_WIDTH; x++)
					{
						if (_cells[y][_randomSets[_currentRandomSet][x]].update())
							cellsUpdated += 1;
					}
					_currentRandomSet = (_currentRandomSet + 1) % RANDOM_SETS_NB;
				}
			}
			cycleTime = currentTime;
		}

		// Reset cell hasMoved & apply next temperature
		for (int y = 0; y < CELL_HEIGHT; y++)
			for (int x = 0; x < CELL_WIDTH; x++)
			{
				_cells[y][x].getMovementBehavior()->hasMoved = false;
				_cells[y][x]._temperature = _cells[y][x]._nextTemperature;
			}

		if (currentTime - previousTime >= 1.0f)
		{
			std::cout << "frames per second: " << frameCount << std::endl;
			frameCount = 0;
			previousTime = currentTime;
		}

		ui.update();

		renderer.render(program, _cells);
		ui.render();

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	ui.shutdown();

	glfwTerminate();
}

Application::~Application()
{
	delete [] _randomSets;
	delete [] _cells;
}
