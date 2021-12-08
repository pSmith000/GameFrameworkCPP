#pragma once
#include "Component.h"
#include "Transform2D.h"

class MoveComponent :
	public Component
{
public:
	MoveComponent();
	MoveComponent(Actor* owner, const char* name, float speed);
	~MoveComponent();
	void start() override;
	void update(float deltaTime) override;

private:
	MathLibrary::Vector2 m_velocity;
	MathLibrary::Vector2 m_moveDirection;
	MathLibrary::Vector2 m_position;
	float m_speed;
};

