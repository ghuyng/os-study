#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/*This function count the numbers of integer in array arr with length = len
that divisible by n                                                      */
int count_divisible(int *arr, int len, int n)
{
    int count = 0;
    for(int i=0; i<len; i++)
    {
        if (arr[i] % n == 0)
            count++;
    }
    return count;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Please provide input file");
        return -1;
    }

    int number;
    int len = 0;
    char *filename = argv[1];
    FILE *file_in = fopen(filename, "r");
    if (!file_in)
        return -1;

    /*Get the number of integers in the file*/
    while (fscanf(file_in, "%d", &number) != EOF)
        len ++;                            
    
    fseek(file_in, 0, SEEK_SET);

    /*Create array to store integers from files*/
    int *num_arr = malloc(len * sizeof(int));
    for(int i=0; i<len; i++)
        fscanf(file_in, "%d", &num_arr[i]);
    
    pid_t child_pid = fork();
    if (child_pid == -1)    /*Fail to fork */
        exit(1);
    if (child_pid == 0)     /*child process*/
    {
        /*Create another process */
        child_pid = fork();
        if (child_pid == -1)/*Fail to fork*/
            exit(1);
        if (child_pid == 0)
            /*This process check for divisible by 3*/
            printf("%d\n", count_divisible(num_arr, len, 3));
        else
            /*This process check for divisible by 7*/
            printf("%d\n", count_divisible(num_arr, len, 7));
    }
    else    /*Parent process*/
        /*This process check for divisible by 11*/
        printf("%d\n", count_divisible(num_arr, len, 11));

    fclose(file_in);
    free(num_arr);

    return 0;
}
        
