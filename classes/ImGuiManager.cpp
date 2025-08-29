#include "ImGuiManager.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ImGuiWindowBase.h"

namespace ImGui
{
	ImGuiManager* ImGuiManager::s_Instance = nullptr;

	ImGuiManager::ImGuiManager(GLFWwindow* window)
		: m_Window(window)
	{
		Setup();
	}

	ImGuiManager::~ImGuiManager()
	{
		Destroy();
	}

	void ImGuiManager::Initialize(GLFWwindow* window)
	{
		if (!s_Instance)
		{
			s_Instance = new ImGuiManager(window);
		}
	}

	void ImGuiManager::Shutdown()
	{
		delete s_Instance;
		s_Instance = nullptr;
	}

	ImGuiManager& ImGuiManager::GetInstance()
	{
		return *s_Instance;
	}

	void ImGuiManager::AddWindow(std::shared_ptr<ImGuiWindowBase> window)
	{
		m_ImGuiWindows.push_back(window);
		window->Initialise();
	}

	void ImGuiManager::Setup()
	{
		// Setup ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		
		// Setup ImGui style
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
	}

	void ImGui::ImGuiManager::Destroy()
	{
		for (std::shared_ptr<ImGuiWindowBase> ImGuiWindow : m_ImGuiWindows)
		{
			ImGuiWindow->Shutdown();
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiManager::Draw()
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Give update to ImGui labels
		for (std::shared_ptr<ImGuiWindowBase> ImGuiWindow : m_ImGuiWindows)
		{
			ImGuiWindow->SetDraw();
			
			ImGuiWindow->PreDraw();
			ImGuiWindow->Draw();

			ImGuiWindow->UnsetDraw();
		}

		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(m_Window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glfwSwapBuffers(m_Window);
	}
}