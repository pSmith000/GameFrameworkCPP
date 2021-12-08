#include "Component.h"

Component::Component()
{
}

Component::Component(Actor* actor, const char* name)
{
	m_name = name;
	m_owner = actor;
}

Component::~Component()
{
}

const char* Component::getName()
{
	return m_name;
}

Actor* Component::getOwner()
{
	return m_owner;
}

void Component::start()
{
}

void Component::update(float deltaTime)
{
}

void Component::draw()
{
}

void Component::end()
{
}

void Component::onCollision(Actor* actor)
{
}
