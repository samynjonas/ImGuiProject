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
		ImGuiWindowBase(std::string windowName, ImGuiWindowFlags windowFlags);
		virtual ~ImGuiWindowBase();

		void SetDraw();
		void UnsetDraw();

		virtual void Initialise() = 0;
		virtual void Draw() = 0;
		virtual void Shutdown() = 0;

	protected:
		void DrawCenteredProgressBar(float value, const ImVec2& size);

	protected:
		std::string m_WindowName;
		ImGuiWindowFlags m_WindowFlags;

	};

	class ImGuiWindowExample : public ImGuiWindowBase
	{
	public:
		ImGuiWindowExample(std::string windowName);
		ImGuiWindowExample(std::string windowName, ImGuiWindowFlags windowFlags);
		~ImGuiWindowExample();

		void Initialise() override;
		void Draw() override;
		void Shutdown() override;
	};

}