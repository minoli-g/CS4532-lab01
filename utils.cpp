#ifndef UTILS
#define UTILS

#include "pthread.h"
#include <iostream>
#include <algorithm>
#include <sysinfoapi.h>
#include <vector>
#include <cmath>
#include <random>
#include <limits>

#include "linkedlist.h"

enum Operations{
    MEMBER, INSERT, DEL
};

// The structure of the data passed to each thread subroutine
struct funcParams {
    std::vector<std::pair<Operations, int>>* operationsPointer;
    int begin;
    int end;
    LinkedList* linkedList;
};

// The subroutine run by each thread
void* run_operations(void* ops){
    struct funcParams* opStruct = (struct funcParams*)ops;
    LinkedList* ll = opStruct->linkedList;

    for (int i = opStruct->begin; i<opStruct->end; i++){
        std::pair<Operations, int> op = (*(opStruct->operationsPointer))[i];
        switch (op.first){
            case MEMBER:
                ll->Member(op.second);
                break;
            case INSERT:
                ll->Insert(op.second);
                break;
            case DEL:
                ll->Delete(op.second);
                break;
        }
    }
    return nullptr;
}

std::vector<int> getRandomNumbersInRange(int start, int end, int n){

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(start, end);
    std::vector<int> ans {};

    for (int i=0; i<n; i++){
        ans.push_back(distrib(gen));
    }
    return ans;
}

std::vector<std::pair<Operations, int>> preAssignOperations(int m, float m_member, 
                                                            float m_insert, float m_delete){

    std::vector<std::pair<Operations, int>> operations { };
    int max = std::numeric_limits<uint16_t>::max();

    // Choose completely random values for member and insert operations
    for (auto n: getRandomNumbersInRange(0, max, m_member*m)){
        operations.push_back(std::pair<Operations, int>(Operations::MEMBER, n));
    }

    std::vector<int> values = getRandomNumbersInRange(0, max, m_insert*m);
    for (auto n: values){
        operations.push_back(std::pair<Operations, int>(Operations::INSERT, n));
    }

    // Get half of the delete operation values randomly
    for (auto n: getRandomNumbersInRange(0, max, m_delete*m/2)){
        operations.push_back(std::pair<Operations, int>(Operations::DEL, n));
    }

    // Get remaining half of delete values from the insert values 
    // This increases the number of chances of actually deleting something from the list
    for (int i=0; i<(m_delete*m/2); i++){
        operations.push_back(std::pair<Operations, int>(Operations::DEL, values[i]));
    }

    // Shuffle the operations vector randomly
    random_shuffle(operations.begin(), operations.end());

    //For debugging purposes, print the operations
    //for (auto op:operations){
        //std::cout<<"@ "<<op.first<<":"<<op.second<<"\n";
    //}
    return operations;
}


int runAllOperations(int num_threads, int n, int m, float m_member, float m_insert, float m_delete){

    srand(time(NULL));

    LinkedList ll = LinkedList();

    // Populate the list with n random numbers between 0 and 2**16 -1 
    std::vector<int> values = getRandomNumbersInRange(0, std::numeric_limits<uint16_t>::max(), n);

    for (auto num:values){
        ll.Insert(num);
    }
    // For debugging purposes
    //ll.Print();
    
    std::vector<std::pair<Operations, int>> operations = preAssignOperations(m, m_member, m_insert, m_delete);

    pthread_t threads[num_threads];
    struct funcParams func_params;

    std::cout << "Starting operations \n";
    long long int start = GetTickCount64();

    // Create and run the threads
    for (long int i=0; i<num_threads; i++){

        func_params.operationsPointer = &operations;
        func_params.begin = i*(m/num_threads);
        func_params.end = func_params.begin + (m/num_threads);
        func_params.linkedList = &ll;

        int t = pthread_create(&threads[i], NULL, run_operations, (void*)&func_params);
 
        if (t != 0){
            std::cout << "Error in thread creation: " << t << "\n";
            exit(0);
        }
    }

    // Synchronize the threads
    for(long int i = 0 ; i < num_threads; ++i){
        void* status;
        int t = pthread_join(threads[i], &status);
        if (t != 0) {
            std::cout << "Error in thread join: " << t << "\n";
            exit(0);
        }
    }

    long long int end = GetTickCount64();
    std::cout << "All operations complete\n";
    std::cout << "Time taken: " << (end-start);
    
    // For debugging purposes
    //ll.Print();

    return (end-start);

}

#endif