/*
    int count1s ()

    Requires: Array containing integers
    Effects: Returns the number of 1s in it.

    This function was given in the assignment - Did not test it appropriately
    
*/

/*
    void * threadCounting(void *id)

    This function will be executed by each created thread.

    Requires: The id of the thread. The id ranges from 0 to n-1 where n=number of threads.
    Effects: Returns the number of ones the threads have counted.
        NO PRECAUTIONS ARE TAKEN TO PREVENT RACE-CONDITIONS. THE RESULT WE GET FROM THE THREADS IS EXPECTED TO BE INCORRECT.

    testcases:
    Array sizes of 100,1000,10000,1000000,10000000,100000000,1000000000 with threads of sizes 1,2,4,8,16,32,64. 
*/




#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

long * array;

long array_length=10000000;
// Global variable to which all threads are writing into
int count=0;
// This will be the result the sequential function returns
int correct_count=0;

int ThreadsNumber=16;

// Sequential Code - Given in the assignment
int count1s ()
 {

 for (int i=0; i<array_length; i++)
 {
        if (array[i] == 1)
    {
        
        correct_count++;
    } 
 }
    return correct_count;
 }

 void * threadCounting(void *id)
 {
    long ID = (long) id;

    long numberofIterations = array_length / ThreadsNumber;

    long startIndex = ID*numberofIterations;

    long endIndex = startIndex+numberofIterations;

    // If this is the last thread, let it iterate till the end of the array
    if(array_length-endIndex<numberofIterations)
    {
        endIndex=array_length;
    }

    for(startIndex;startIndex<endIndex;startIndex++)
        {
            if(array[startIndex] == 1)
                count++;
        } 
 }

 int main()
{
    clock_t start_time,check_time1, end_time;
    
    array = (long*)malloc(array_length * sizeof(long));

    for (long i=0;i<array_length;i++)
    {
        array[i] = rand() % 5 + 1;
    }
    // Start time for sequential function
    start_time=clock();
    correct_count = count1s();
    //End time for sequential function and also start time of parallel programming
    check_time1=clock();
  
    pthread_t T[ThreadsNumber];

    for(int i=0;i<ThreadsNumber;i++)
    {
        pthread_create(&T[i],NULL,&threadCounting,(void*)i);
    }

    for (int i=0;i<ThreadsNumber;i++)
    {
        pthread_join(T[i],NULL);
    }

    end_time=clock();
    double total_Time_sequential = ((double) (check_time1-start_time)) / CLOCKS_PER_SEC;
    double total_Time_parallel = ((double) (end_time-check_time1)) / CLOCKS_PER_SEC;

   printf(" # Threads: %d\n",ThreadsNumber);
   printf("Time Taken sequentially: %f\n",total_Time_sequential);
   printf("Correct count of 1's= %d\n", correct_count);
   printf("Time Taken - parallel programming: %f\n",total_Time_parallel);
   printf("Count of 1s with multiple threads: %d\n",count);
   free(array);

    return 0;

}