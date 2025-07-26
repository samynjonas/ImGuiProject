#include <iostream>
#include "classes/UdpListenerBase.h"
#include "classes/ImGuiManager.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include "classes/ImGuiWindowBase.h"
#include "classes/TelemetryWindow.h"

int main()
{
    // Initialize GLFW
    if (!glfwInit()) 
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Create a GLFW windowed mode window and OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui Desktop", NULL, NULL);
    if (!window) 
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    ImGui::ImGuiManager::Initialize(window);

    std::shared_ptr<ImGui::Telemetry::TelemetryWindow> telemetryWindow = std::make_shared<ImGui::Telemetry::TelemetryWindow>("Telemetry");
    ImGui::ImGuiManager::GetInstance().AddWindow(telemetryWindow);

    // --- MAIN LOOP ---
    while (!glfwWindowShouldClose(window))
    {
        ImGui::ImGuiManager::GetInstance().Draw();
    }

    // Cleanup
    ImGui::ImGuiManager::Shutdown();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
