#include "MoveComponent.h"
#include <Vector2.h>
#include "Actor.h"
#include "raylib.h"

MoveComponent::MoveComponent()
{
}

MoveComponent::MoveComponent(Actor* owner, const char* name, float speed)
{
    m_speed = speed;
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::start()
{
}

void MoveComponent::update(float deltaTime)
{
    m_velocity = m_moveDirection.normalize() * m_speed * deltaTime;

    m_position = getOwner()->getTransform()->getWorldPosition();

    m_position = m_position + m_velocity;
}
