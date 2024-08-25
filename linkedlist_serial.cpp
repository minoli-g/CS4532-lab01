#include "linkedlist.h"
#include <iostream>

LinkedList::LinkedList(){
    std::cout << "Creating a serial linked list \n";
    head = nullptr;
}

bool LinkedList::Member(uint16_t value){
    Node* tmp = head;
    while ( tmp != nullptr){
        if (tmp->value == value){
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

void LinkedList::Insert(uint16_t value){
    // Assuming the value doesn't exist in the list already

    Node* newNode = new Node(value);

    if (head==nullptr){
        head = newNode;
        return;
    }

    Node* tmp = head;
    while ( tmp->next != nullptr ){
        tmp = tmp->next;
    }
    tmp->next = newNode;
}

void LinkedList::Delete(uint16_t value){

    if (head->value == value){
        head = head->next;
        return;
    }

    Node* prev = head;
    Node* tmp = prev->next;

    while ( tmp->next != nullptr ){

        if (tmp->value == value){
            prev->next = tmp->next;
            tmp->next = nullptr;
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}
