#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argv, char* argn)
{
    int shmid;
    char c;
    char *shm, *s;

    /* Use ftok to generate a key associated with a file */
    key_t key = ftok("/tmp/shm", 'a');

    /* Create/Locate the memory segment */
    // TODO: add code to create memory segment using shmget()
    //       size is fixed to 128
    //       key is provided by key_t key

    /* Attach the memory segment to our address space */
    // TODO: add code to attach memory segment using shmat()
    //       the return address is assign to pointer *shm

    /* Read whatever data put in the memory */
    for(s = shm; *s != NULL;s++)
        printf("%c\n", *s);

    /* Acknowledge the read is completed */
    *shm = '*';

    return 0;
}
