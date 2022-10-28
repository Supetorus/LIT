#include "Component.h"
namespace wl
{

	Component::Component(const Object &parent) :
		parent(parent),
		transform(parent.m_transform)
	{}

}