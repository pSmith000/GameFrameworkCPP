#pragma once
#include <exception>

template<typename T>
class DynamicArray
{
public:
    DynamicArray();
    ~DynamicArray();

    void addItem(T item);
    void addItems(T item[], int size);
    bool removeItem(T item);
    void sortItems();
    T getItem(int index);
    int getLength();
    bool contains(T value);

    T operator [](int index);
private:
    T* m_items;
    int m_length;
};

template<typename T>
inline DynamicArray<T>::DynamicArray()
{
    m_length = 0;
    m_items = nullptr;
}

template<typename T>
inline DynamicArray<T>::~DynamicArray()
{
}

template<typename T>
void DynamicArray<T>::addItem(T item)
{
    //Create a new array with a size one greater than our old array
    T* tempArray = new T[getLength() + 1];
    //Copy the values from the old array to the new array
    for (int i = 0; i < getLength(); i++)
    {
        tempArray[i] = m_items[i];
    }

    //Set the last value in the new array to be the actor we want to add
    tempArray[getLength()] = item;
    //Set old array to hold the values of the new array
    delete[] m_items;
    m_items = tempArray;
    m_length++;
}

template<typename T>
inline void DynamicArray<T>::addItems(T items[], int size)
{
    for (int i = 0; i < size; i++)
    {
        addItem(items[i]);
    }
}

template<typename T>
bool DynamicArray<T>::removeItem(T item)
{
    //Check to see if the actor was null
    if (!item || getLength() <= 0)
    {
        return false;
    }

    bool itemRemoved = false;
    //Create a new array with a size one less than our old array
    T* tempArray = new T[getLength() - 1];
    //Create variable to access tempArray index
    int j = 0;
    //Copy values from the old array to the new array
    for (int i = 0; i < getLength(); i++)
    {
        if (item != m_items[i] || itemRemoved)
        {
            tempArray[j] = m_items[i];
            j++;
        }
        else if (!itemRemoved)
        {
            itemRemoved = true;
        }
    }

    //Set the old array to the new array
    if (itemRemoved)
    {
        delete[] m_items;
        m_items = tempArray;
        m_length--;
    }
    //Return whether or not the removal was successful
    return itemRemoved;
}

template<typename T>
void DynamicArray<T>::sortItems()
{
    int j = 0;
    T key;

    for (int i = 1; i < m_length; i++)
    {
        key = m_items[i];
        j = i - 1;

        while (j >= 0 && m_items[j] > key)
        {
            m_items[j + 1] = m_items[j];
            j--;
        }
        m_items[j + 1] = key;
    }
}

template<typename T>
inline T DynamicArray<T>::getItem(int index)
{
    if (index < 0 || index >= getLength())
        return T();

    return m_items[index];
}

template<typename T>
inline int DynamicArray<T>::getLength()
{
    return m_length;
}

template<typename T>
inline bool DynamicArray<T>::contains(T value)
{
    for (int i = 0; i < m_length; i++)
    {
        if (m_items[i] == value)
            return true;
    }
    return false;
}

template<typename T>
inline T DynamicArray<T>::operator[](int index)
{
    if (index > 0 || index < getLength())
        return m_items[index];

    throw std::exception("Index was outside the bounds of the array loser");
}
