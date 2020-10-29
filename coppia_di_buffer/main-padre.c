#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "buffer.h"

int main()
{

    int buf1_id;
    int buf2_id;
    buffer *buf1;
    buffer *buf2;
    int sem_id;

    buf1_id = /* TBD: Creazione shared memory buffer singolo */

    if (buf1_id < 0)
    {
        perror("Errore creazione SHM buf1");
        exit(1);
    }

    buf2_id = /* TBD: Creazione shared memory buffer singolo */

    if (buf2_id < 0)
    {
        perror("Errore creazione SHM buf2");
        exit(1);
    }

    sem_id = /* TBD: Creazione vettore semafori */

    if (sem_id < 0)
    {
        perror("Errore creazione semafori");
        exit(1);
    }

    buf1 = /* TBD: Attach shared memory buffer singolo */

    if (buf1 == (void *)-1)
    {
        perror("Errore attach SHM buf1");
        exit(1);
    }

    buf2 = /* TBD: Attach shared memory buffer singolo */

    if (buf2 == (void *)-1)
    {
        perror("Errore attach SHM buf2");
        exit(1);
    }

    /* TBD: inizializzazione stato buf1 e buf2 */

    /* TBD: inizializzazione semafori */


    /* TBD: Creazione processo produttore */
    
    /* TBD: Creazione processo consumatore */


    for (int i = 0; i < 2; i++)
    {
        wait(NULL);
    }

    shmctl(buf1_id, IPC_RMID, NULL);
    shmctl(buf2_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);
}