//Kanishka Bansal
//Mizanur Rahman

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

//number of element
int n;

/*
 * funtion to find Max value in a separate thread
 */
void* findMax(void *vargp)
{
    int *array = (int *)vargp;

    int max = INT_MIN;
    for(int i = 0; i< n; i++)
    {
        if(array[i]>=max){
            max = array[i];
        }
    }

    int* result = malloc(sizeof(result));
    *result= max;
    return result;

}

/*
 * funtion to find Min value in a separate thread
 */
void* findMin(void *vargp)
{
    int *array = (int *)vargp;

    int min = INT_MAX;
    for(int i = 0; i< n; i++)
    {
        if(array[i]<=min){
            min = array[i];
        }
    }

    int* result = malloc(sizeof(result));
    *result= min;
    return result;
}

/*
 * funtion to find average value in a separate thread
 */
void* findAvg(void *vargp)
{
    int *array = (int* )vargp;

    int sum = 0;
    for(int i = 0; i< n; i++)
    {
        sum += array[i];
    }
    float avg = (float)sum/n;

    float* result = malloc(sizeof(avg));
    *result = avg;
    return result;
}

void main(int argc, char* argv[]){

    //first argument is the name of pragramm itself
    n = argc-1;

    if(n<2){
        printf("you didn't enter numbers in argument\n");
        return;
    }

    //create array to store numbers
    int* array = malloc(n*sizeof(int));

    //first argument (0 index) is the name of pragramm itself , so start from index 1
    for(int i = 1; i<= n ; i++){

        array[i-1] = atoi(argv[i]);
    }


    /*
     * create threads to perform operation
     * arguments of pthread_create:
     * 1.id of threate
     * 2.not required here
     * 3.function name
     * 4.arguments to be pass to the function
     */
    pthread_t tid1,tid2,tid3;
    pthread_create(&tid1,NULL,findMax,array);
    pthread_create(&tid2,NULL,findMin,array);
    pthread_create(&tid3,NULL,findAvg,array);

    /*
     * pthread_join keep main function wait for calculations to be finished
     * arguments are:
     * 1. thread id
     * 2. return value from thread
     */
    void* max = malloc(sizeof(max));
    void* min = malloc(sizeof(min));
    void* avg = malloc(sizeof(avg));
    pthread_join(tid1,&max);
    pthread_join(tid2,&min);
    pthread_join(tid3,&avg);


    printf("Max:%d\n",*((int*)max));
    printf("Min:%d\n",*((int*)min));
    printf("Avg:%f\n",*((float*)avg));

    free(max);
    free(min);
    free(avg);
    free(array);
    printf("\n");

}


