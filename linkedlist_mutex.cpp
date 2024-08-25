#include "linkedlist.h"
#include <iostream>

static pthread_mutex_t mutex;

LinkedList::LinkedList(){
    std::cout << "Creating a linked list with mutex \n";
    head = nullptr;
}

bool LinkedList::Member(uint16_t value){

    pthread_mutex_lock(&mutex);

    Node* tmp = head;
    while ( tmp != nullptr){
        if (tmp->value == value){

            pthread_mutex_unlock(&mutex);
            return true;
        }
        tmp = tmp->next;
    }

    pthread_mutex_unlock(&mutex);
    return false;
}

void LinkedList::Insert(uint16_t value){
    // Assuming the value doesn't exist in the list already
    pthread_mutex_lock(&mutex);

    Node* newNode = new Node(value);

    if (head==nullptr){
        head = newNode;

        pthread_mutex_unlock(&mutex);
        return;
    }

    Node* tmp = head;
    while ( tmp->next != nullptr ){
        tmp = tmp->next;
    }
    tmp->next = newNode;

    pthread_mutex_unlock(&mutex);
}

void LinkedList::Delete(uint16_t value){

    pthread_mutex_lock(&mutex);

    if (head->value == value){
        head = head->next;

        pthread_mutex_unlock(&mutex);
        return;
    }

    Node* prev = head;
    Node* tmp = prev->next;

    while ( tmp->next != nullptr ){

        if (tmp->value == value){
            prev->next = tmp->next;
            tmp->next = nullptr;

            pthread_mutex_unlock(&mutex);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    pthread_mutex_unlock(&mutex);
}
