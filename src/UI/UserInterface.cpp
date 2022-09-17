#include "UserInterface.h"

UserInterface::UserInterface(GLFWwindow& window, const int& winWidth, const int& winHeight, int& selectedElement)
	: _window(window), WIN_WIDTH(winWidth), WIN_HEIGHT(winHeight), _selectedElement(selectedElement)
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

	ImGui::Begin("test");

	for (int i = 0; i < 4; i++)
	{
		char text[32];
		snprintf(text, 32, "Element %d", i);
		if (ImGui::Selectable(text, _selectedElement == i))
			_selectedElement = i;
	}

	ImGui::Text("This a test sentence");
	ImGui::End();
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
