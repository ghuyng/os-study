#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define NUM_THREADS 20

struct thread_data{
    int tid;
    unsigned long nPoints;
} thread_data_arr[NUM_THREADS];

static unsigned long count = 0;

pthread_mutex_t lock;
/*This function does a Monter-Carlo simulation by randomly picking (nPoints) points*/
/*inside the square and count the number of points land inside the circle          */
void *monte_carlo(void *thread_arg)
{
    struct thread_data *data = (struct thread_data*)thread_arg;
    unsigned long total = data->nPoints;
    int *seedp = &(data->tid);
    double x, y;
    for(int i=0; i<total; i++)
    {
        /*Randomize x and y in range [-1, 1]*/
        x = (double)rand_r(seedp)/RAND_MAX * 2 - 1;
        y = (double)rand_r(seedp)/RAND_MAX * 2 - 1;
        if (x*x + y*y <= 1)
        {
            pthread_mutex_lock(&lock);
            count ++;
            pthread_mutex_unlock(&lock);
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    /*time_t start = time(NULL);*/
    if(argc != 2) {
        fprintf( stderr , "usage : a.out <integer value>\n" ) ;
        return -1;
    }

    if(atol(argv[1]) < 0) {
        fprintf(stderr , "%d must be >= 0\n" , atoi(argv[1])) ;
        return -1;
    }

    pthread_t       threads[NUM_THREADS];
    pthread_attr_t  attr[NUM_THREADS];
    unsigned long total = atol(argv[1]);
    unsigned long nPoints = total/NUM_THREADS;  //number of points that each threads will do

    srand(time(NULL));
    for(int i=0; i<NUM_THREADS; i++)
    {
        pthread_attr_init(&attr[i]);
        thread_data_arr[i].tid = (int)threads[i];
        thread_data_arr[i].nPoints = nPoints;
        pthread_create(&threads[i], &attr[i], monte_carlo, (void*)(&thread_data_arr[i]));
    }

    /*if total is not divisible by NUM_THREADS then the main thread will do the remaining points*/
    if (total % NUM_THREADS != 0)
    {
        double x, y;
        int remain = total % NUM_THREADS;
        for(int i=0; i<remain; i++)
        {
            /*Randomize x and y in range [-1, 1]*/
            x = (double)rand()/RAND_MAX * 2 - 1;
            y = (double)rand()/RAND_MAX * 2 - 1;
            if (x*x + y*y <= 1)
            {
                pthread_mutex_lock(&lock);
                count++;
                pthread_mutex_unlock(&lock);
            }
        }
    }


    for(int i=0; i<NUM_THREADS; i++)
        pthread_join(threads[i],NULL);

    double pi = 4 * (double)count/total;
    printf("pi = %f\n", pi);
    
    /*printf("total time = %f", difftime(time(NULL),start));*/

    pthread_exit(NULL);
}
