#pragma once
#include <string>

namespace lit
{
	class Transform;

	/// <summary>
	/// Converts wide (unicode) strings to strings
	/// </summary>
	/// <param name="wstr">The string to be converted</param>
	/// <returns></returns>
	std::string wstrToStr(std::wstring wstr);

	/// <summary>
	/// Uses keyboard input to modify the transform.
	/// </summary>
	/// <param name="transform">The transform to be modified</param>
	/// <param name="moveSpeed">How fast to move</param>
	/// <param name="scaleSpeed">How fast to scale</param>
	/// <param name="rotationSpeed">How fast to rotate</param>
	/// <param name="dt">Time since last frame</param>
	void ManipulateTransform(Transform &transform, float moveSpeed, float scaleSpeed, float rotationSpeed, float dt);
}
