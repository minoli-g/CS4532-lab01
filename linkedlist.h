#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstdint>
#include <iostream>

class Node{
    public:
        uint16_t value;
        Node* next;

        Node(){
            this->value = 0;
            this->next = nullptr;
        }

        Node(uint16_t value){
            this->value = value;
            this->next = nullptr;
        }
};

class LinkedList{
    private:
        Node* head;

    public:
        LinkedList();
        bool Member(uint16_t value);
        void Insert(uint16_t value);
        void Delete(uint16_t value);

        void Print(){
            std::cout<<"\n";
            Node* tmp = head;
            while ( tmp != nullptr){
                std::cout<<tmp->value<<"---";
                tmp = tmp->next;
            }
            std::cout<<"\n";
        }
};

#endif