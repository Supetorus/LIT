#pragma once
#include <string>

namespace wl
{
	class Transform;

	std::string wstrToStr(std::wstring wstr);

	void ManipulateTransform(Transform &transform, float moveSpeed, float scaleSpeed, float rotationSpeed, float dt);
}
