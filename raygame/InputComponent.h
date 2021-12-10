#pragma once
#include "Component.h"
class InputComponent :
	public Component
{
private:
	float m_moveLeft;
	float m_moveRight;
	float m_moveUp;
	float m_moveDown;
};

