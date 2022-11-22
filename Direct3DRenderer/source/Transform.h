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
			inline bool operator==(f3 right) const
			{
				return x == right.x && y == right.y && z == right.z;
			}
			inline bool operator!=(f3 right) const
			{
				return !(*this == right);
			}
		};
		const static Transform identity;
		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);
		inline bool operator==(Transform right) const
		{
			return position == right.position && rotation == right.rotation && scale == right.scale;
		}
		inline bool operator!=(Transform right) const
		{
			return !(*this == right);
		}
		f3 position{};
		f3 scale{ 1, 1, 1 };
		f3 rotation{};
	};

}
