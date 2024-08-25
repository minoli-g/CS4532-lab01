The code consists of two sections - 
1. main.cpp - this constructs a single linked list implementation 
            and executes the operations with the given parameters.

    The linked list implementations are contained in different .cpp files, 
    all implementing the same specification given in linkedlist.h file

    To test a particular linked list implementation, the relevant .cpp file
    must be provided as an argument when compiling the executable. 

    Example - To run a serial linked list implementation, 

    a) Compile the files using 
        g++ -o main linkedlist_serial.cpp 

    b) Execute with the required parameters in the following order:
        Number of threads, n, m, m_member, m_insert, m_delete

        For Case 1, this would be:
        main 1 1000 10000 0.99 0.005 0.005

2. driver.cpp - this runs the tests needed for analysis.

    Internally, it calculates the required sample sizes and statistics.

    Input - the number of the case required to be tested.
    Output - the mean and std of the times taken to run that case on the
            provided linked list implementation, for 1,2,4 and 8 threads.

    a) Compilation (as an example, for the mutex implementation): 
        g++ -o tests driver.cpp linkedlist_mutex.cpp

    b) Execution (as an example, for Case 2):
        tests 2
