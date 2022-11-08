#pragma once

namespace wl
{

	class Transform
	{
	public:
		struct f3
		{
			float x{};
			float y{};
			float z{};
		};
		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);
		f3 position{};
		f3 scale{ 1, 1, 1 };
		f3 rotation{};
	};

}
