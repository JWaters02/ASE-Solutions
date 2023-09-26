#include <iostream>

#include "Coordinate.h"
#include "SinglyLinkedList.h"
#include "DynamicArray.h"

void coordinate();
void singlyLinkedList();
void dynamicArray();

int main()
{
    //coordinate();
    //singlyLinkedList();
    dynamicArray();

    return 0;
}

void coordinate()
{
    Coordinate p1 = Coordinate(1,2); // stack allocation
    Coordinate p2(3,7); // stack allocation
    p1.xco = 4;
    p2.yco = p2.yco + 5;
    p1.display();
    p2.display();

    Coordinate* coPtr = new Coordinate(7,8);  // heap allocation
    coPtr->display(); // same as (*coPtr).display();

    Coordinate co2 = *coPtr;
    Coordinate* coPtr2 = &co2;

    delete coPtr; // heap deallocation
    coPtr = nullptr; // set to null pointer to avoid dangling pointer
}

void singlyLinkedList()
{
    SinglyLinkedList list;
    list.insert('a');
    list.insert('b');
    list.insert('c');
    list.insert('d');
    list.insert('e');

    list.display();

    std::cout << std::boolalpha << "c: " << list.search('c') << std::endl;
    std::cout << std::boolalpha << "g: " << list.search('g') << std::endl;

    SinglyLinkedList list2;
    list2.insert_back('a');
    list2.insert_back('b');
    list2.insert_back('c');
    list2.insert_back('d');
    list2.insert_back('e');

    list2.display();
}

void dynamicArray()
{
    DynamicArray<char> arr;
    arr.push_back('a');
    arr.push_back('b');
    arr.push_back('c');
    arr.push_back('d');
    arr.push_back('e');

    arr.display();

    arr.pop_back();
    arr.pop_back();

    arr.display();

    std::cout << arr.read_at(0) << std::endl;
    std::cout << arr.read_at(1) << std::endl;
    std::cout << arr.read_at(2) << std::endl;
    std::cout << arr.read_at(3) << std::endl; // should be empty (\0)

    arr.write_at(0, 'z');
    arr.write_at(1, 'y');
    arr.write_at(2, 'x');
    arr.write_at(3, 'w'); // should be empty, as size and capacity are 3

    arr.display();

    DynamicArray<int> arr2;
    arr2.push_back(2);
    arr2.push_back(3);

    arr2.pop_back();

    arr2.display();
}