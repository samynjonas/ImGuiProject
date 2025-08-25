#include <iostream>
#include "classes/ImGuiManager.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include "classes/ImGuiWindowBase.h"
#include "classes/TelemetryConverters/TelemetryReader.h"

#include "classes/Windows/CarInputWindow.h"
#include "classes/Windows/CarMechanicsWindow.h"
#include "classes/Windows/LapWindow.h"
#include "classes/Windows/MapWindow.h"

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

    std::shared_ptr<::Telemetry::TelemetryReader> telemetryReader = std::make_shared<::Telemetry::TelemetryReader>();

    std::shared_ptr<ImGui::Telemetry::CarInputWindow> carInputWindow = std::make_shared<ImGui::Telemetry::CarInputWindow>("CarInput");
    carInputWindow->SetTelemetryReader(telemetryReader);
    ImGui::ImGuiManager::GetInstance().AddWindow(carInputWindow);

    std::shared_ptr<ImGui::Telemetry::CarMechanicsWindow> carMechanicsWindow = std::make_shared<ImGui::Telemetry::CarMechanicsWindow>("CarMechanics");
    carMechanicsWindow->SetTelemetryReader(telemetryReader);
    ImGui::ImGuiManager::GetInstance().AddWindow(carMechanicsWindow);

    std::shared_ptr<ImGui::Telemetry::LapWindow> lapWindow = std::make_shared<ImGui::Telemetry::LapWindow>("LapWindow");
    lapWindow->SetTelemetryReader(telemetryReader);
    ImGui::ImGuiManager::GetInstance().AddWindow(lapWindow);

    std::shared_ptr<ImGui::Telemetry::MapWindow> mapWindow = std::make_shared<ImGui::Telemetry::MapWindow>("MapWindow");
    mapWindow->SetTelemetryReader(telemetryReader);
    ImGui::ImGuiManager::GetInstance().AddWindow(mapWindow);

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
