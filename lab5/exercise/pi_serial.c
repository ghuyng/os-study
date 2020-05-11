#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*This function does a Monter-Carlo simulation by randomly picking (nPoints) points*/
/*inside the square and count the number of points land inside the circle          */
unsigned long monte_carlo(unsigned long nPoints)
{
    unsigned long count_in_circle = 0;
    double x, y;
    srand(time(NULL));
    for(int i=0; i<nPoints; i++)
    {
        /*Randomize x and y in range [-1, 1]*/
        x = (double)rand()/RAND_MAX * 2 - 1;
        y = (double)rand()/RAND_MAX * 2 - 1;
        if (x*x + y*y <= 1)
            count_in_circle ++;
    }

    return count_in_circle;
}

int main(int argc, char *argv[])
{
    timer_t start = time(NULL);
    if(argc != 2) {
        fprintf( stderr , "usage : a.out <integer value>\n" ) ;
        return -1;
    }

    if(atoi(argv[1]) < 0) {
        fprintf(stderr , "%d must be >= 0\n" , atoi(argv[1])) ;
        return -1;
    }
    unsigned long nPoints = atol(argv[1]);
    unsigned long nInCircle = monte_carlo(nPoints);

    double pi = 4 * (double)nInCircle/nPoints;
    printf("pi = %f\n", pi);
    
    printf("total time = %f", difftime(time(NULL), start));
    return 0;
}
