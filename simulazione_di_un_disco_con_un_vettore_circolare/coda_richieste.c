#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>

#include "coda_richieste.h"

coda_richieste *inizializza_coda()
{
    int shm_id;
    int sem_id;
    coda_richieste *c;

    sem_id = /* TBD: Creazione vettore semafori */

    if (sem_id < 0)
    {
        perror("Errore creazione semafori");
        exit(1);
    }

    /* TBD: Inizializzazione vettore semafori */


    shm_id = /* TBD: Creazione shared memory */

    if (shm_id < 0)
    {
        perror("Errore creazione SHM coda richieste");
        exit(1);
    }

    c = /* TBD: Attach shared memory */

    if (c == (void *)-1)
    {
        perror("Errore attach SHM");
        exit(1);
    }


    /* TBD: Inizializzazione shared memory */


    return c;
}

void preleva_richiesta(coda_richieste *c, richiesta *r)
{

    /* TBD: Inizio consumazione */


    printf("[%d] Consumazione in coda: %d\n", getpid(), c->coda);

    r->posizione = /* TBD */;
    r->processo = /* TBD */;


    /* TBD: Fine consumazione */
}

void inserisci_richiesta(coda_richieste *c, richiesta *r)
{
    /* TBD: Inizio produzione */

    printf("[%d] Produzione in testa: %d\n", getpid(), c->testa);

    /* TBD */ = r->posizione;
    /* TBD */ = r->processo;


    /* TBD: Fine produzione */
}

void rimuovi_coda(coda_richieste *c)
{
    semctl(c->sem_id, 0, IPC_RMID);
    shmctl(c->shm_id, IPC_RMID, NULL);
}
