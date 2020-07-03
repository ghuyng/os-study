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
    shmid = shmget(key, 128, IPC_CREAT);

    /* Attach the memory segment to our address space */
    // TODO: add code to attach memory segment using shmat()
    //       the return address is assign to pointer *shm
    shm = (char*) shmat(shmid, NULL, 0);

    /* Now we put some thing into the memory for the
     * other process to read */
    s = shm;
    for(c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = NULL;

    /* We wait until the process acknowledge by
     * changing the first character of the memory */
    while (*shm != '*')
        sleep(1);

    //TODO: Implement code to remove the memory segment using shmctl()
    shmctl(shmid, IPC_RMID, (struct shmid_ds *)0);

    return 0;
}
