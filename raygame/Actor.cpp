
#include <cmath>
#include "Actor.h"
#include "Transform.h"

Actor::~Actor()
{
    delete m_transform;
}


Actor::Actor(float x, float y, const char* name = "Actor")
{
    m_transform = new Transform2D(this);
    m_transform->setLocalPosition({ x,y });
}

void Actor::start()
{
    m_started = true;
}



void Actor::onCollision(Actor* other)
{
}

void Actor::update(float deltaTime)
{
}

void Actor::draw()
{
}

void Actor::debug()
{
}


void Actor::end()
{
    m_started = false;
}
