#include <iostream>
#include "utils.cpp"

int main(int argc, char* argv[]){

    int num_threads = std::stoi(argv[1]);
    int n = std::stoi(argv[2]);
    int m = std::stoi(argv[3]);
    float m_member = std::stof(argv[4]);
    float m_insert = std::stof(argv[5]);
    float m_delete = std::stof(argv[6]);

    printf("Number of threads=%d, n=%d, m=%d, m_member=%.3f, m_insert=%.3f, m_delete=%.3f\n",
            num_threads, n, m, m_member, m_insert, m_delete);

    return runAllOperations(num_threads, n, m, m_member, m_insert, m_delete);

}