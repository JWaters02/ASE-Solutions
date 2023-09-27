#ifndef ASE_SOLUTIONS_DYNAMICARRAY_H
#define ASE_SOLUTIONS_DYNAMICARRAY_H

#include <iostream>

template <typename T>
class DynamicArray
{
public:
    DynamicArray();
    ~DynamicArray()
    {
        delete[] pointer;
    }

    void push_back(T data);
    void pop_back();
    T read_at(int index) const;
    void write_at(int index, T data);

    void display() const;

private:
    int size;
    int capacity;
    T* pointer;
};

template <typename T>
DynamicArray<T>::DynamicArray()
{
    size = 0;
    capacity = 0;
    pointer = nullptr;
}

template <typename T>
void DynamicArray<T>::push_back(T data)
{
    if (size == capacity)
    {
        capacity == 0 ? capacity = 1 : capacity *= 2;
        T* newPointer = new T[capacity];
        for (int i = 0; i < size; i++)
        {
            newPointer[i] = pointer[i];
        }
        delete[] pointer;
        pointer = newPointer;
    }
    pointer[size] = data;
    size++;
}

template <typename T>
void DynamicArray<T>::pop_back()
{
    if (size > 0)
    {
        size--;
    }
}

template <typename T>
T DynamicArray<T>::read_at(int index) const
{
    if (index >= 0 && index < size)
    {
        return pointer[index];
    }
    return '\0';
}

template <typename T>
void DynamicArray<T>::write_at(int index, T data)
{
    if (index >= 0 && index < size)
    {
        pointer[index] = data;
    }
}

template <typename T>
void DynamicArray<T>::display() const
{
    for (int i = 0; i < size; i++)
    {
        std::cout << pointer[i] << ' ';
    }
    std::cout << std::endl;
}

#endif //ASE_SOLUTIONS_DYNAMICARRAY_H
