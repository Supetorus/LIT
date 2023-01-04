#include "Component.h"
namespace lit
{

	Component::Component(const Object &parent) :
		parent(parent),
		transform(parent.m_transform)
	{}

}