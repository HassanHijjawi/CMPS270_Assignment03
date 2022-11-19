#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<time.h>

long * array;
long array_length=10000000;
int count=0;
int correct_count=0;
int ThreadsNumber=16;


int count1s ()
 {

    int count = 0;

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
    clock_t start_time,end_time;
    start_time=clock();
    array = (long*)malloc(array_length * sizeof(long));

    for (long i=0;i<array_length;i++)
    {
        array[i] = rand() % 5 + 1;
    }

    correct_count = count1s();
    // Put the the number of threads between []
    pthread_t T[16];
    
    // Number of iterations should be equal to the number of threads
    for(int i=0;i<16;i++)
    {
        pthread_create(&T[i],NULL,&threadCounting,(void*)i);
    }

    for (int i=0;i<1;i++)
    {
        pthread_join(T[i],NULL);
    }

    end_time=clock();
    double total_Time = ((double) (end_time-start_time)) / CLOCKS_PER_SEC;

   printf(" # Threads: %d\n",ThreadsNumber);
   printf("Time Taken: %f\n",total_Time);
   printf("Correct count of 1's= %d\n", correct_count);
   printf("Count of 1s with multiple threads: %d\n",count);
   free(array);

    return 0;

}