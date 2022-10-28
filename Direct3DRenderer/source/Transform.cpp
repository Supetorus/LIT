#include "Transform.h"
namespace wl
{

	void Transform::SetPosition(float x, float y, float z)
	{
		posX = x;
		posY = y;
		posZ = z;
	}

	void Transform::SetRotation(float x, float y, float z)
	{
		angleX = x;
		angleY = y;
		angleZ = z;
	}

}