#pragma once
#include "TextureLoader.h"
#include "Math/Vector.h"

namespace ImGui
{
	struct GLImageRotation
	{
		enum Enum : int
		{
			R0 = 0,
			R90 = 1,
			R180 = 2,
			R270 = 3
		};
	};

	struct GLImageParams
	{
		ImTextureID image = 0;

		Math::Vec2 top_left = Math::Vec2(0, 0);
		Math::Vec2 size = Math::Vec2(0, 0);

		Math::Vec2 uv_min = Math::Vec2(0, 0);
		Math::Vec2 uv_max = Math::Vec2(1, 1);

		GLImageRotation::Enum rotation = GLImageRotation::R0;
		bool flip_y = false;

		float zoom = 1.f;
		Math::Vec2 pan = Math::Vec2(0, 0);
	};

	void AddImage(GLImageParams const& imageParams, bool drawDebugOutline = false);
}
