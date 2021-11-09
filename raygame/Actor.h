#pragma once
#include "Transform.h"

class Actor
{
public:
    Actor();
    ~Actor();

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="name">The name of this actor.</param>
    Actor(float x, float y, const char* name);

    /// <summary>
    /// </summary>
    /// <returns>If the actors start function has been called.</returns>
    bool getStarted() { return m_started; }

    /// <returns> The transform attached to this actor.</returns>
    Transform2D* getTransform() { return m_transform; }

    /// <summary>
    /// Called during the first update after an actor is added to a scene.
    /// </summary>
    virtual void start();

    /// <summary>
    /// Called when a collision between this actor and another occurs. 
    /// </summary>
    /// <param name="other">The actor this actor collided with.</param>
    virtual void onCollision(Actor* other);

    virtual void update(float deltaTime);
    virtual void draw();
    virtual void debug();
    virtual void end();

protected:
    char* m_name;

private:
    bool m_started;
    Transform2D* m_transform;
};

