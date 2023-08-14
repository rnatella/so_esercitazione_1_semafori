#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "coda_richieste.h"

#define DIM_DISCO 20

void Schedulatore(coda_richieste *c)
{

    int disco[DIM_DISCO];
    int posizione_corrente = 0;


    for (int i = 0; i < 25; i++)
    {

        /* TBD: Effettuare la consumazione */

        printf("[%d] Prelevo richiesta: posizione=%d, processo=%d\n", getpid(), r.posizione, r.processo);

        int attesa = abs(posizione_corrente - (int)r.posizione);

        printf("[%d] Attesa Schedulatore... (%d secondi)\n", getpid(), attesa);

        sleep(attesa);

        disco[r.posizione] = r.processo;

        posizione_corrente = r.posizione;
    }
}

void Utente(coda_richieste *c)
{

    for (int i = 0; i < 5; i++)
    {

        printf("[%d] Richiesta Utente: posizione=%d, processo=%d\n", getpid(), r.posizione, r.processo);

        /* TBD: Effettuare la produzione */
    }
}

int main()
{

    /* TBD: Allocazione coda richieste, chiamando "inizializza_coda()" */


    /* TBD: Creazione del processo Schedulatore */


    /* TBD: Creazione dei processi Utente */


    /* TBD: Attesa terminazione processi figli */


    /* TBD: De-allocazione coda richieste, chiamando "rimuovi_coda()" */
}
