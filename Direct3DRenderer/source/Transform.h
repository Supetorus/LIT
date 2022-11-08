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
		//f3 position{};
		//f3 scale{};
		//f3 rotation{};
		float posX{};
		float posY{};
		float posZ{};
		float angleX{};
		float angleY{};
		float angleZ{};
	};

}
