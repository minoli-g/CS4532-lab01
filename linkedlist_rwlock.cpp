#include "linkedlist.h"
#include <iostream>

static pthread_rwlock_t rwlock;

LinkedList::LinkedList(){
    std::cout << "Creating a linked list with read-write lock \n";
    head = nullptr;
}

bool LinkedList::Member(uint16_t value){

    pthread_rwlock_rdlock(&rwlock);

    Node* tmp = head;
    while ( tmp != nullptr){
        if (tmp->value == value){

            pthread_rwlock_unlock(&rwlock);
            return true;
        }
        tmp = tmp->next;
    }

    pthread_rwlock_unlock(&rwlock);
    return false;
}

void LinkedList::Insert(uint16_t value){
    // Assuming the value doesn't exist in the list already
    pthread_rwlock_wrlock(&rwlock);

    Node* newNode = new Node(value);

    if (head==nullptr){
        head = newNode;

        pthread_rwlock_unlock(&rwlock);
        return;
    }

    Node* tmp = head;
    while ( tmp->next != nullptr ){
        tmp = tmp->next;
    }
    tmp->next = newNode;

    pthread_rwlock_unlock(&rwlock);
}

void LinkedList::Delete(uint16_t value){

    pthread_rwlock_wrlock(&rwlock);

    if (head->value == value){
        head = head->next;

        pthread_rwlock_unlock(&rwlock);
        return;
    }

    Node* prev = head;
    Node* tmp = prev->next;

    while ( tmp->next != nullptr ){

        if (tmp->value == value){
            prev->next = tmp->next;
            tmp->next = nullptr;

            pthread_rwlock_unlock(&rwlock);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    pthread_rwlock_unlock(&rwlock);
}
