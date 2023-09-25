#include <iostream>

#include "Coordinate.h"
#include "SinglyLinkedList.h"

void coordinate();
void singlyLinkedList();

int main()
{
    coordinate();
    singlyLinkedList();

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