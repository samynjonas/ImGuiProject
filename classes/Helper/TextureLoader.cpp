#include "TextureLoader.h"
#include <stdexcept>
#include "../external/stb/stb_image.h"

namespace ImGui
{
    GLImage LoadTexture2D(const std::string& path, bool linear_filter)
    {
        int w = 0, h = 0, comp = 0;
        stbi_set_flip_vertically_on_load(false);
        unsigned char* pixels = stbi_load(path.c_str(), &w, &h, &comp, 4);
        if (!pixels) throw std::runtime_error("Failed to load image: " + path);

        GLImage tex = 0;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linear_filter ? GL_LINEAR : GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        // glGenerateMipmap(GL_TEXTURE_2D); // enable if you want mipmaps

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(pixels);
        return tex;
    }
}

