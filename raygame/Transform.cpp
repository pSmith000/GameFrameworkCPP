#include "Transform.h"
#include <cmath>
using namespace MathLibrary;

Transform2D::Transform2D(Actor* owner)
{
    m_globalMatrix = new Matrix3();
    m_localMatrix = new Matrix3();
    m_translation = new Matrix3();
    m_rotation = new Matrix3();
    m_scale = new Matrix3();
    m_children = nullptr;
    m_owner = owner;
}

Transform2D::~Transform2D()
{
    delete m_globalMatrix;
    delete m_localMatrix;
    delete m_rotation;
    delete m_translation;
    delete m_scale;
    delete[] m_children;
}

MathLibrary::Vector2 Transform2D::getForward()
{
    if (m_shouldUpdateTransforms)
    {
        updateTransforms();
        m_shouldUpdateTransforms = false;
    }
    return MathLibrary::Vector2(m_globalMatrix->m11, m_globalMatrix->m21).getNormalized();
}

void Transform2D::setForward(MathLibrary::Vector2 value)
{
    MathLibrary::Vector2 lookPosition = getWorldPosition() + value.getNormalized();
    lookAt(lookPosition);
}

MathLibrary::Vector2 Transform2D::getWorldPosition()
{
    if (m_shouldUpdateTransforms)
    {
        updateTransforms();
        m_shouldUpdateTransforms = false;
    }
    return MathLibrary::Vector2(m_globalMatrix->m02, m_globalMatrix->m12);
}

void Transform2D::setWorldPostion(MathLibrary::Vector2 value)
{
    if (m_parent)
    {
        setLocalPosition(value + m_parent->getWorldPosition());
    }
    else
    {
        setLocalPosition(value);
    }
    m_shouldUpdateTransforms = true;
}

MathLibrary::Vector2 Transform2D::getLocalPosition()
{
    if (m_shouldUpdateTransforms)
    {
        updateTransforms();
        m_shouldUpdateTransforms = false;
    }
    return MathLibrary::Vector2(m_localMatrix->m02, m_localMatrix->m12);
}

void Transform2D::setLocalPosition(MathLibrary::Vector2 value)
{
    *m_translation = MathLibrary::Matrix3::createTranslation(value);
    m_shouldUpdateTransforms = true;
}

void Transform2D::addChild(Transform2D* child)
{
    //Create a new array with a size one greater than our old array
    Transform2D** appendedArray = new Transform2D * [m_childCount + 1];
    //Copy the values from the old array to the new array
    for (int i = 0; i < m_childCount; i++)
    {
        appendedArray[i] = m_children[i];
    }

    child->m_parent = this;

    //Set the last value in the new array to be the actor we want to add
    appendedArray[m_childCount] = child;
    //Set old array to hold the values of the new array
    m_children = appendedArray;
    m_childCount++;
}

bool Transform2D::removeChild(int index)
{
    //Check to see if the index is outside the bounds of our array
    if (index < 0 || index >= m_childCount)
    {
        return false;
    }

    bool actorRemoved = false;

    //Create a new array with a size one less than our old array 
    Transform2D** newArray = new Transform2D * [m_childCount - 1];
    //Create variable to access tempArray index
    int j = 0;
    //Copy values from the old array to the new array
    for (int i = 0; i < m_childCount; i++)
    {
        //If the current index is not the index that needs to be removed,
        //add the value into the old array and increment j
        if (i != index)
        {
            newArray[j] = m_children[i];
            j++;
        }
        else
        {
            actorRemoved = true;
        }
    }
    m_children[index]->m_parent = nullptr;
    //Set the old array to be the tempArray
    m_children = newArray;
    m_childCount--;
    return actorRemoved;
}

bool Transform2D::removeChild(Transform2D* child)
{
    //Check to see if the actor was null
    if (!child)
    {
        return false;
    }

    bool actorRemoved = false;
    //Create a new array with a size one less than our old array
    Transform2D** newArray = new Transform2D * [m_childCount - 1];
    //Create variable to access tempArray index
    int j = 0;
    //Copy values from the old array to the new array
    for (int i = 0; i < m_childCount; i++)
    {
        if (child != m_children[i])
        {
            newArray[j] = m_children[i];
            j++;
        }
        else
        {
            actorRemoved = true;
        }
    }
    child->m_parent = nullptr;
    //Set the old array to the new array
    m_children = newArray;
    m_childCount--;
    //Return whether or not the removal was successful
    return actorRemoved;
}

void Transform2D::setScale(MathLibrary::Vector2 scale)
{
    *m_scale = MathLibrary::Matrix3::createScale(scale);
    m_shouldUpdateTransforms = true;
}

void Transform2D::scale(MathLibrary::Vector2 scale)
{
    *m_scale = *m_scale * MathLibrary::Matrix3::createScale(scale);
    m_shouldUpdateTransforms = true;
}

void Transform2D::setRotation(float radians)
{
    *m_rotation = MathLibrary::Matrix3::createRotation(radians);
    m_shouldUpdateTransforms = true;
}

void Transform2D::rotate(float radians)
{
    *m_rotation = *m_rotation * MathLibrary::Matrix3::createRotation(radians);
    m_shouldUpdateTransforms = true;
}

void Transform2D::lookAt(MathLibrary::Vector2 position)
{
    //Find the direction that the actor should look in
    MathLibrary::Vector2 direction = (position - getWorldPosition()).getNormalized();

    //Use the dotproduct to find the angle the actor needs to rotate
    float dotProd = MathLibrary::Vector2::dotProduct(getForward(), direction);
    if (abs(dotProd) > 1)
        return;
    float angle = (float)acos(dotProd);

    //Find a perpindicular vector to the direction
    MathLibrary::Vector2 perp = MathLibrary::Vector2(direction.y, -direction.x);

    //Find the dot product of the perpindicular vector and the current forward
    float perpDot = MathLibrary::Vector2::dotProduct(perp, getForward());

    //If the result isn't 0, use it to change the sign of the angle to be either positive or negative
    if (perpDot != 0)
        angle *= -perpDot / abs(perpDot);

    rotate(angle);
}

void Transform2D::updateTransforms()
{
    *m_localMatrix = *m_translation * *m_rotation * *m_scale;

    if (m_parent)
        *m_globalMatrix = *(m_parent->m_globalMatrix) * (*m_localMatrix);
    else
        *m_globalMatrix = *m_localMatrix;
}
