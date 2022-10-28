#pragma once

namespace wl
{

	class Transform
	{
	public:
		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		float posX{};
		float posY{};
		float posZ{};
		float angleX{};
		float angleY{};
		float angleZ{};
	};

}
