#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

#include "utils.cpp"

int runAllOperationsMuted(int num_threads, int n, int m, float m_member, float m_insert, float m_delete){
    // Mute the outputs while running each sample
    std::cout.setstate(std::ios_base::failbit); 
    int ans = runAllOperations(num_threads, n, m, m_member, m_insert, m_delete);
    std::cout.clear();
    return ans;
}

int main(int argc, char* argv[]){
    // Runs all the test cases for each scenario, for the linked list version compiled with it

    int testScenario = std::stoi(argv[1]);
    int n,m;
    float m_member, m_insert, m_delete;

    switch (testScenario){
        case 1:
            n=1000; m=10000; m_member=0.99; m_insert=0.005; m_delete=0.005;
            break;
        case 2:
            n=1000; m=10000; m_member=0.9; m_insert=0.05; m_delete=0.05;
            break;
        case 3:
            n=1000; m=10000; m_member=0.5; m_insert=0.25; m_delete=0.25;
            break;  
        default:
            std::cout << "Invalid scenario";
            exit(0);          
    }

    int thread_counts[4] {1,2,4,8};

    // Test with each thread count
    for(int num_threads:thread_counts){

        printf("Thread count = %d\n", num_threads);
        std::vector<int> times {};

        // Start with sample size 100
        printf("\t Checking 100 samples...\n");
        for (int i=0; i<100; i++){
            times.push_back(runAllOperationsMuted(num_threads, n, m, m_member, m_insert, m_delete));
        }

        // Calculate required sample size
        int sum = std::accumulate(times.begin(), times.end(), 0);
        double mean = sum / times.size();

        int sq_sum = std::inner_product(times.begin(), times.end(), times.begin(), 0);
        double stdev = std::sqrt(sq_sum / times.size() - mean * mean);

        // N = (100*z*s/r*x')^2, for 95% confidence z = 1.960, r = accuracy = 5
        int rqd_num = pow( (196*stdev)/(5*mean), 2);
        printf("\t Required num of samples = %d\n", rqd_num);

        // Get more samples if needed - cushion the rqd num by 10 
        if (rqd_num > 100){
            printf("\t Collecting more samples...\n");
            for (int i=100; i<rqd_num+10; i++){
                times.push_back(runAllOperationsMuted(num_threads, n, m, m_member, m_insert, m_delete));
            }
            // Recalculate mean, std dev
            sum = std::accumulate(times.begin(), times.end(), 0);
            mean = sum / times.size();
            sq_sum = std::inner_product(times.begin(), times.end(), times.begin(), 0);
            stdev = std::sqrt(sq_sum / times.size() - mean * mean);
        }

        printf("\t Mean = %.2f, Std.dev = %.2f\n\n", mean, stdev);
    }
    return 1;
}