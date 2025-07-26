#include "ImGuiWindowBase.h"
#include "ImGuiManager.h"

// Base
namespace ImGui
{
	ImGuiWindowBase::ImGuiWindowBase(std::string windowName)
		: m_WindowName(windowName)
	{

	}

	ImGuiWindowBase::~ImGuiWindowBase()
	{

	}

	void ImGuiWindowBase::SetDraw()
	{
		ImGui::Begin(m_WindowName.c_str());
	}

	void ImGuiWindowBase::UnsetDraw()
	{
		ImGui::End();
	}
}

// Example
namespace ImGui
{
	ImGuiWindowExample::ImGuiWindowExample(std::string windowName)
		: ImGuiWindowBase(windowName)
	{

	}

	ImGuiWindowExample::~ImGuiWindowExample()
	{

	}

	void ImGuiWindowExample::Initialise()
	{
		std::cout << "Initialise ImGui Example Window " << m_WindowName << std::endl;
	}

	void ImGuiWindowExample::Shutdown()
	{
		std::cout << "Shutdown ImGui Example Window " << m_WindowName << std::endl;
	}

	void ImGuiWindowExample::Draw()
	{
		ImGui::Text("Example ImGui Window");
	}
}