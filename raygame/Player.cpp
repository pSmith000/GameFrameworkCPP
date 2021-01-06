#include "Player.h"
#include "Game.h"
#include "raylib.h"
#include <iostream>

Player::Player(float x, float y, float collisionRadius, const char* spriteFilePath) : Actor(x, y, collisionRadius, spriteFilePath)
{
}

void Player::update(float deltatime)
{
    //Gets the player's input to determine which direction the actor will move on each axis 
    int xDirection = -Game::getKeyDown(KEY_A) + Game::getKeyDown(KEY_D);
    int yDirection = -Game::getKeyDown(KEY_W) + Game::getKeyDown(KEY_S);
    
    setVelocity(MathLibrary::Vector2(xDirection, yDirection));

    if (getVelocity().getMagnitude() > 0)
        lookAt(getWorldPosition() + getVelocity().getNormalized());

    Actor::update(deltatime);
}

void Player::debug()
{

    std::cout << "X: " << getVelocity().x << std::endl << "Y: "<< getVelocity().y << std::endl;
}
