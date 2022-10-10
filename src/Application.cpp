#include "Application.h"

#include "Instrumentor.h"

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
	_randomSets = new std::vector<int>[RANDOM_SETS_NB];
	// Fill all random sets with numbers from 0 to cell_width - 1
	for (int i = 0; i < CELL_WIDTH; i++)
		for (int j = 0; j < RANDOM_SETS_NB; j++)
			_randomSets[j].push_back(i);
	
	// Shuffle numbers in sets
	auto rng = std::default_random_engine {};
	for (int i = 0; i < RANDOM_SETS_NB; i++)
		std::shuffle(_randomSets[i].begin(), _randomSets[i].end(), rng);

	// Print random numbers
	/*for (int j = 0; j < RANDOM_SETS_NB; j++)
	{
		std::cout << std::endl;
		for (int i = 0; i < CELL_WIDTH; i++)
			std::cout << _randomSets[j][i] << " ";
	}*/
}

void Application::loop()
{
	_selectedElement = 1; // Sand by default
	_selectedBrush = 0; // Square brush by default
	_selectedFilter = 0;
	_currentRandomSet = 0;

	_cells = new Cell* [CELL_HEIGHT];
	for (int y = 0; y < CELL_HEIGHT; y++)
	{
		_cells[y] = new Cell [CELL_WIDTH];
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
		WIN_HEIGHT
	};
	CellsArrayData CellsArrayData {
		CELL_SIZE,
		CELL_WIDTH,
		CELL_HEIGHT,
		_cells
	};

	InputManager input(windowData, CellsArrayData, _selectedElement, _selectedBrush, &_hoveredCell);
	ShaderProgram program("src/shaders/shader.vert", "src/shaders/shader.frag");
	GridRenderer renderer(CELL_WIDTH, CELL_HEIGHT, CELL_SIZE, _selectedFilter);
	UserInterface ui(windowData, _selectedElement, _selectedBrush, _selectedFilter, &_hoveredCell);
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

		if (currentTime - cycleTime >= 0.015f)
		{
			for (int i = 0; i < 2; i++)
			{
				for (int y = 0; y < CELL_HEIGHT; y++)
				{
					for (int x = 0; x < CELL_WIDTH; x++)
					{
						_cells[y][_randomSets[_currentRandomSet][x]].update();
					}
					_currentRandomSet = (_currentRandomSet + 1) % RANDOM_SETS_NB;
				}
			}
			cycleTime = currentTime;
		}

		int gaz = 0;
		int liquid = 0;
		int solid = 0;
		double averageTemp = 0;
		for (int y = 0; y < CELL_HEIGHT; y++)
			for (int x = 0; x < CELL_WIDTH; x++)
			{
				_cells[y][x].getMovementBehavior()->hasMoved = false;
				_cells[y][x]._temperature = _cells[y][x]._nextTemperature;
				_cells[y][x]._nextTemperature = _cells[y][x]._temperature;

				if (_cells[y][x].getType() == CellType::Gazeous)
					gaz++;
				else if (_cells[y][x].getType() == CellType::Liquid)
					liquid++;
				else if (_cells[y][x].getType() == CellType::Solid)
					solid++;
				
				averageTemp += _cells[y][x]._temperature;
			}

		if (currentTime - previousTime >= 1.0f)
		{
			std::cout << frameCount << std::endl;
			std::cout << "GAZ: " << gaz << " | LIQUID: " << liquid << " | SOLID: " << solid << std::endl;
			std::cout << "Average temperature: " << (averageTemp / (CELL_HEIGHT*CELL_WIDTH)) << std::endl;

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
