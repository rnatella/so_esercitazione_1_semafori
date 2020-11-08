#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

#include "buffer.h"

int main() {

    printf("[%d] Creazione shared memory\n", getpid());

    key_t chiave_shm = /* TBD: Definire una chiave */

    int shm_id = /* TBD: Allocare una memoria condivisa */

    if(shm_id < 0) {
        perror("Errore creazione shared memory");
        exit(1);
    }

    buffer * b = /* TBD: Ottenere un puntatore alla memoria condivisa */

    if(b == (void*)-1) {
        perror("Errore attach shared memory");
        exit(1);
    }


    /* TBD: Inizializzare la memoria condivisa */



    printf("[%d] Creazione semafori\n", getpid());

    key_t sem_chiave = /* TBD: Definire una chiave */

    int sem_id = /* TBD: Allocare un vettore di semafori */

    if(sem_id < 0) {
        perror("Errore creazione semafori");
        exit(1);
    }


    /* TBD: Inizializzare il vettore di semafori */





    printf("[%d] Creazione processo scrittore\n", getpid());

    /* TBD: Creare un processo scrittore, ed eseguire "main_scrittore" */

    


    for(int i=0; i<2; i++) {

        printf("[%d] Creazione processo lettore\n", getpid());

        /* TBD: Creare un processo lettore, ed eseguire "main_lettori" */
    }




    printf("[%d] In attesa di terminazione dei processi\n", getpid());

    /* TBD: Attendere la terminazione dei processi figli */



    printf("[%d] Deallocazione risorse\n", getpid());

    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);
}
