#include "Application.h"

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
	double currentTime = glfwGetTime();
    if ( currentTime - previousTime >= 1.0 )
    {
		std::cout << frameCount << std::endl;

        frameCount = 0;
        previousTime = currentTime;
    }
}

void Application::loop()
{
	ShaderProgram program("src/shaders/shader.vert", "src/shaders/shader.frag");

	double previousTime = glfwGetTime();

	int frameCount = 0;

	GridRenderer renderer(WIN_WIDTH / 2, WIN_HEIGHT / 2);

	while (!glfwWindowShouldClose(_window) && glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
    	frameCount++;
		
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		printTime(previousTime, frameCount);
		renderer.render(program);

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
	glfwTerminate();
}

