#include "Actor.h"
#include "Transform2D.h"
#include <string.h>
#include "Collider.h"
#include "Component.h"

Actor::Actor()
{
    m_transform = new Transform2D(this);
}

Actor::~Actor()
{
    delete m_transform;
}


Actor::Actor(float x, float y, const char* name = "Actor")
{
    //Initialze default values
    m_transform = new Transform2D(this);
    m_transform->setLocalPosition({ x,y });
    m_name = name;
}



void Actor::onCollision(Actor* other)
{
}

Component* Actor::addComponent(Component* component)
{
    //Create a new array with a size one greater than our old array
    Component** appendedArray = new Component * [m_componentCount + 1];
    //Copy the values from the old array to the new array
    for (int i = 0; i < m_componentCount; i++)
    {
        appendedArray[i] = m_comp[i];
    }

    //Set the last value in the new array to be the actor we want to add
    appendedArray[m_componentCount] = component;
    //Set old array to hold the values of the new array
    m_comp = appendedArray;
    m_componentCount++;

    return component;
}

bool Actor::removeComponent(Component* component)
{
    //Check to see if the actor was null
    if (!component)
    {
        return false;
    }

    bool componentRemoved = false;
    //Create a new array with a size one less than our old array
    Component** newArray = new Component * [m_componentCount - 1];
    //Create variable to access tempArray index
    int j = 0;
    //Copy values from the old array to the new array
    for (int i = 0; i < m_componentCount; i++)
    {
        if (component != m_comp[i])
        {
            newArray[j] = m_comp[i];
            j++;
        }
        else
        {
            componentRemoved = true;
        }
    }
    //Set the old array to the new array
    if (componentRemoved)
    {
        m_comp = newArray;
        m_componentCount--;
    }
    //Return whether or not the removal was successful
    return componentRemoved;
}

bool Actor::removeComponent(const char* name)
{
    //Check to see if the actor was null
    if (name == nullptr)
    {
        return false;
    }

    bool componentRemoved = false;
    //Create a new array with a size one less than our old array
    Component** newArray = new Component * [m_componentCount - 1];
    //Create variable to access tempArray index
    int j = 0;
    //Copy values from the old array to the new array
    for (int i = 0; i < m_componentCount; i++)
    {
        if (name != m_comp[i]->getName())
        {
            newArray[j] = m_comp[i];
            j++;
        }
        else
        {
            componentRemoved = true;
        }
    }
    //Set the old array to the new array
    if (componentRemoved)
    {
        m_comp = newArray;
        m_componentCount--;
    }
    //Return whether or not the removal was successful
    return componentRemoved;
}

Component* Actor::getComponent(const char* name)
{
    for (int i = 0; i < m_componentCount; i++)
    {
        if (name == m_comp[i]->getName())
        {
            return m_comp[i];
        }
    }
    return nullptr;
}

void Actor::start()
{
    m_started = true;
}

void Actor::update(float deltaTime)
{
}

void Actor::draw()
{
}

void Actor::end()
{
    m_started = false;
}

void Actor::onDestroy()
{
    //Removes this actor from its parent if it has one
    if (getTransform()->getParent())
        getTransform()->getParent()->removeChild(getTransform());
}

bool Actor::checkForCollision(Actor* other)
{
    //Call check collision if there is a collider attached to this actor
    if (m_collider)
        return m_collider->checkCollision(other);

    return false;
}