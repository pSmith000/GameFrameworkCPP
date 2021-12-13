#include "Component.h"

Component::Component()
{
	m_owner = nullptr;
	m_name = nullptr;
	m_started = false;
}

Component::Component(const char* name)
{
	m_name = name;
}

void Component::assignOwner(Actor* owner)
{
	if (getOwner())
		return;

	m_owner = owner;
}
