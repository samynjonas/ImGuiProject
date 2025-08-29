#pragma once
#include <iostream>
#include <vector>

struct GLFWwindow;
namespace ImGui
{
	class ImGuiWindowBase;
	class ImGuiManager
	{
	public:
		static ImGuiManager& GetInstance();
		static void Initialize(GLFWwindow* window);
		static void Shutdown();

		void Setup();
		void Draw();
		void Destroy();
		void AddWindow(std::shared_ptr<ImGuiWindowBase> window);

	private:
		ImGuiManager(GLFWwindow* window);
		~ImGuiManager();

		GLFWwindow* m_Window;
		std::vector<std::shared_ptr<ImGuiWindowBase>> m_ImGuiWindows;

		static ImGuiManager* s_Instance;
	};
}
