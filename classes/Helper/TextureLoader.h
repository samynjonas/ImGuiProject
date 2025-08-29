#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

typedef GLuint GLImage;
namespace ImGui
{
	GLImage LoadTexture2D(const std::string& path, bool linear_filter = true);
}
