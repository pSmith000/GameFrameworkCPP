#include "Player.h"
#include "InputComponent.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Transform2D.h"

void Player::start()
{
	Actor::start();

	m_inputComponent = addComponent<InputComponent>();
	m_moveComponent = addComponent<MoveComponent>();
	m_moveComponent->setMaxSpeed(10);
	m_spriteComponent = dynamic_cast<SpriteComponent*>(addComponent(new SpriteComponent("images/player.png")));

	//Set spawn point
	//Set move speed
	//Set position clamps
}

void Player::update(float deltaTime)
{
	Actor::update(deltaTime);

	MathLibrary::Vector2 moveDirection = m_inputComponent->getMoveAxis();

	m_moveComponent->setVelocity(moveDirection * 500);
}
