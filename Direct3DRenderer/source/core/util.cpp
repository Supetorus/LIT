#include "util.h"

#include "Input.h"
#include "Transform.h"

#include <string>
#include <wchar.h>
#include <cstring>
#include <stdlib.h>

namespace wl
{
	std::string wstrToStr(std::wstring wstr)
	{
		return { wstr.begin(), wstr.end() };
	}
	void ManipulateTransform(Transform &transform, float moveSpeed, float scaleSpeed, float rotationSpeed, float dt)
	{
		float speed = 1.0f;
		const char space = 0x20;
		const char shift = 0x10;
		if (Input::Instance.GetKeyDown('A'))	transform.position.x -= moveSpeed * dt;
		if (Input::Instance.GetKeyDown('D'))	transform.position.x += moveSpeed * dt;
		if (Input::Instance.GetKeyDown('W'))	transform.position.z += moveSpeed * dt;
		if (Input::Instance.GetKeyDown('S'))	transform.position.z -= moveSpeed * dt;
		if (Input::Instance.GetKeyDown(space))	transform.position.y += moveSpeed * dt;
		if (Input::Instance.GetKeyDown(shift))	transform.position.y -= moveSpeed * dt;

		const char left = 0x25;
		const char right = 0x27;
		const char up = 0x26;
		const char down = 0x28;
		if (Input::Instance.GetKeyDown(left))	transform.rotation.y -= rotationSpeed * dt;
		if (Input::Instance.GetKeyDown(right))	transform.rotation.y += rotationSpeed * dt;
		if (Input::Instance.GetKeyDown(up))		transform.rotation.x -= rotationSpeed * dt;
		if (Input::Instance.GetKeyDown(down))	transform.rotation.x += rotationSpeed * dt;
		
		const char lessThan = 0xBC;
		const char greaterThan = 0xBE;
		if (Input::Instance.GetKeyDown(lessThan))
		{
			transform.scale.x += scaleSpeed * dt;
			transform.scale.y += scaleSpeed * dt;
			transform.scale.z += scaleSpeed * dt;
		}
		if (Input::Instance.GetKeyDown(greaterThan))
		{
			transform.scale.x -= scaleSpeed * dt;
			transform.scale.y -= scaleSpeed * dt;
			transform.scale.z -= scaleSpeed * dt;
		}
	}
}
