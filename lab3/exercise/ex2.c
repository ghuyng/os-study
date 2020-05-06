#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int create_process_EF();
int create_process_GI();

int main(int argc, char **argv) //Process A
{
    pid_t b,c,d;
    /*printf("A\n");*/

    /*Create process B*/
    b = fork();
    if (b == -1) //Fail to fork
        exit(1);
    if (b == 0)  //Process B
    {
        /*printf("B\n");*/
        /*Stop process B here to wait for process A create process C,D */
        kill(getpid(), SIGSTOP);

        /*When B recieves signal SIGCONT, it will continue to fork E and F*/
        if (create_process_EF() != 0) //Fail to fork E, F
            exit(1);

        kill(getpid(), SIGSTOP);
    }
    else   //Continue of process A
    {
        /*Wait for process B to stop by signal SIGSTOP*/
        waitpid(b, NULL, WUNTRACED);

        /*Create process C*/
        c = fork();
        if (c == -1) //Fail to fork
            exit(1);
        if (c == 0) //Process C
        {
            /*printf("C\n");*/
            /*Stop process C here to wait for process A to create process D*/
            kill(getpid(), SIGSTOP);

            /*When C recieves signal SIGCONT, it will continue to fork() G and G fork() I*/
            if (create_process_GI() != 0) //Fail to fork G, I
                exit(1);

            kill(getpid(), SIGSTOP);
        }
        else  //Continue of process A
        {
            /*Wait for process C to stop by signal SIGSTOP */
            waitpid(c, NULL, WUNTRACED);

            /*Create process D*/
            d = fork();
            if (d < 0)  //Fail to fork
                exit(1);
            if (d == 0) //Process D
            {
                /*printf("D\n");*/
                kill(getpid(), SIGSTOP);
            }
            else
            {
                /*Wait for process D complete*/
                waitpid(d, NULL, WUNTRACED);

                /*Send signal for process B to continue create process E, F*/
                kill(b , SIGCONT);
                /*Wait for B to complete create E,F before C can create G, I */
                waitpid(b, NULL, WUNTRACED);
                
                /*Send signal for process C to continue create process G, I*/
                kill(c, SIGCONT);
                waitpid(c, NULL, WUNTRACED);

                /* Sleep to see the result in htop */
                sleep(2);
            }
        }
    }
    return 0;
}

/*This function is for process B to fork() process E as left-child of B and*/
/*fork process F as right-child of B (create in order E then F)            */
/*Return 0 if success or -1 if fail to fork                                */
int create_process_EF()
{
    pid_t e,f;
    /*Create process E*/
    e = fork();
    if (e == -1) // Fail to fork
        return -1;
    if (e == 0) //Process E
    {
        /*printf("E\n");*/
        kill(getpid(),SIGSTOP);
    }
    else  //Continue process B
    {
        /*Wait for process E complete*/
        waitpid(e, NULL, WUNTRACED);

        /*Create process F*/
        f = fork();
        if (f == -1) //Fail to fork
            return -1;
        if (f == 0) //Process F
        {
            /*printf("F\n");*/
            kill(getpid(),SIGSTOP);
        }
        else    //Continue process B
            /*Wait for process F complete*/
            waitpid(f, NULL, WUNTRACED);
    }
    return 0;
}

/*This function is for process C to fork() process G  and                  */
/*process G fork() process I(C ---> G ---> I)                              */
/*Return 0 if success or -1 if fail to fork                                */
int create_process_GI()
{
    pid_t g, i;

    /*Create process G*/
    g = fork();
    if (g < 0)  //Fail to fork
        return -1;
    if (g == 0)    //Process G
    {
        /*printf("G\n");*/
        /*Create process I*/
        i = fork();
        if (i < 0)  //Fail to fork
            return -1;
        if (i == 0)  //Process I
        {
            /*printf("I\n");*/
            kill(getpid(), SIGSTOP);
        }
        else //continue process G
        {
            /*Wait for process I complete*/
            waitpid(i, NULL, WUNTRACED);
            kill(getpid(), SIGSTOP);
        }
    }
    else      //Continue process C   
        /*Wait for process G complete*/
        waitpid(g, NULL, WUNTRACED);

    return 0;
}
