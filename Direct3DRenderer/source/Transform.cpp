#include "Transform.h"
namespace wl
{

	void Transform::SetPosition(float x, float y, float z)
	{
		position = { x, y, z };
	}

	void Transform::SetRotation(float x, float y, float z)
	{
		rotation = { x, y, z };
	}

	void Transform::SetScale(float x, float y, float z)
	{
		scale = { x, y, z };
	}

}