#include "Application.h"

#include "Instrumentor.h"

Application::Application(const int& width, const int& height)
	: WIN_WIDTH(width), WIN_HEIGHT(height)
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

void printTime(double& previousTime, int& frameCount)
{
}

void Application::loop()
{
	const int CELL_SIZE = 5;
	const int CELL_WIDTH = WIN_WIDTH / CELL_SIZE;
	const int CELL_HEIGHT = WIN_HEIGHT / CELL_SIZE;

	ShaderProgram program("src/shaders/shader.vert", "src/shaders/shader.frag");

	GridRenderer renderer(CELL_WIDTH, CELL_HEIGHT, CELL_SIZE);

	_cells = new Cell* [CELL_HEIGHT];
	for (int y = 0; y < CELL_HEIGHT; y++)
	{
		_cells[y] = new Cell [CELL_WIDTH];
		for (int x = 0; x < CELL_WIDTH; x++)
		{
			_cells[y][x].setPosition(glm::vec2(x, y));
			_cells[y][x].setCells(_cells);
			_cells[y][x].setWidth(CELL_WIDTH);
			_cells[y][x].setHeight(CELL_HEIGHT);
			_cells[y][x].setType(CellType::Gazeous);
			_cells[y][x].setMovementBehavior(new IMovementBehavior(&(_cells[y][x])));
		}
	}

	double previousTime = glfwGetTime();
	double cycleTime = glfwGetTime();
	int frameCount = 0;

	while (!glfwWindowShouldClose(_window) && glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		frameCount++;
		double currentTime = glfwGetTime();


		if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT)) {
			double mouseX, mouseY;
			glfwGetCursorPos(_window, &mouseX, &mouseY);
			if (mouseX >= 0 && mouseX < WIN_WIDTH && mouseY >= 0 && mouseY < WIN_HEIGHT)
			{
				Cell& cell = _cells[(int)(mouseY / CELL_SIZE)][(int)(mouseX / CELL_SIZE)];
				CellFactory::configureSandCell(cell);
			}
		}
		if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_RIGHT)) {
			double mouseX, mouseY;
			glfwGetCursorPos(_window, &mouseX, &mouseY);
			if (mouseX >= 0 && mouseX < WIN_WIDTH && mouseY >= 0 && mouseY < WIN_HEIGHT)
			{
				Cell& cell = _cells[(int)(mouseY / CELL_SIZE)][(int)(mouseX / CELL_SIZE)];
				//CellFactory::configureWaterCell(cell);
				CellFactory::configureRockCell(cell);
			}
		}

		if (currentTime - cycleTime >= 0.015f)
		{
			for (int i = 0; i < 2; i++)
			{
				for (int y = 0; y < CELL_HEIGHT; y++)
				{
					//std::vector<int> v(CELL_WIDTH);
					//std::iota (std::begin(v), std::end(v), 0);
					for (int x = 0; x < CELL_WIDTH; x++)
					{
						//int random = rand() % v.size();
						//_cells[y][v[random]].update();
						//v.erase(v.begin() + random);

						_cells[y][x].update();
					}
				}
			}
			cycleTime = currentTime;
		}

		int gaz = 0;
		int liquid = 0;
		int solid = 0;
		for (int y = 0; y < CELL_HEIGHT; y++)
			for (int x = 0; x < CELL_WIDTH; x++)
			{
				if (_cells[y][x].getMovementBehavior())
					_cells[y][x].getMovementBehavior()->hasMoved = false;

				if (_cells[y][x].getType() == CellType::Gazeous)
					gaz++;
				else if (_cells[y][x].getType() == CellType::Liquid)
					liquid++;
				else if (_cells[y][x].getType() == CellType::Solid)
					solid++;
			}


		if (currentTime - previousTime >= 1.0f)
		{
			std::cout << frameCount << std::endl;
			std::cout << "GAZ: " << gaz << " | LIQUID: " << liquid << " | SOLID: " << solid << std::endl;

			frameCount = 0;
			previousTime = currentTime;
		}

		renderer.render(program, _cells);

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
	glfwTerminate();
}

Application::~Application()
{
	delete [] _cells;
}
