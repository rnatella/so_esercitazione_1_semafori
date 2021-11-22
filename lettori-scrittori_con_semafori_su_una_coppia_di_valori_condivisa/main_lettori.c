#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

#include "buffer.h"

int main()
{
    printf("[%d] Avvio lettore\n", getpid());



    key_t chiave_shm = /* TBD: Definire una chiave */

    int shm_id = /* TBD: Acquisire la memoria condivisa (allocata dal padre) */

    if(shm_id < 0) {
        perror("Errore creazione shared memory");
        exit(1);
    }

    buffer * b = /* TBD: Ottenere un puntatore alla memoria condivisa */

    if(b == (void*)-1) {
        perror("Errore attach shared memory");
        exit(1);
    }


    key_t sem_chiave = /* TBD: Definire una chiave */

    int sem_id = /* TBD: Acquisire il vettore di semafori (allocato dal padre) */

    if (sem_id < 0)
    {
        perror("Errore semget()");
        exit(1);
    }


    srand(getpid());

    for(int i=0; i<5; i++) {

        sleep(1);

        int val_1 = 0;
        int val_2 = 0;

        leggi_buffer(b, sem_id, &val_1, &val_2);
    }



    return 0;

}
