#pragma once
#include <string>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace ImGui
{
	class ImGuiManager;
	class ImGuiWindowBase
	{
	public:
		ImGuiWindowBase(std::string windowName);
		virtual ~ImGuiWindowBase();

		void SetDraw();
		void UnsetDraw();

		virtual void Initialise() = 0;
		virtual void Draw() = 0;
		virtual void Shutdown() = 0;

	protected:
		std::string m_WindowName;

	};

	class ImGuiWindowExample : public ImGuiWindowBase
	{
	public:
		ImGuiWindowExample(std::string windowName);
		~ImGuiWindowExample();

		void Initialise() override;
		void Draw() override;
		void Shutdown() override;
	};

}