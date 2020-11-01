#include "processi.h"
#include "semafori.h"

#include <sys/wait.h>
#include <limits.h>
#include <unistd.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#define MESSAGGIO_DISP 0
#define SPAZIO_DISP 1

int inizializza_semafori()
{
    int sem_id = /* TBD: usare semget() per allocare un vettore,
                  *      con una coppia di semafori */

    if (sem_id < 0)
    {
        perror("Impossibile creare il semaforo per la mutua esclusione");
        exit(1);
    }

    /* Valori iniziali: 0 (messaggio disponibile), 1 (spazio disponibile) */

    /* TBD: inizializzare i semafori */

    return sem_id;
}

void figlio(int *vettore,
            int *buffer,
            int sem_id,
            int elemento_iniziale,
            int qta_elementi)
{

    /* TBD: aggiungere dentro questa funzione delle chiamate a
     *      Wait_Sem() e Signal_Sem() per realizzare lo schema
     *      produttore-consumatore con buffer singolo */

    int minimo = INT_MAX;

    for (int i = elemento_iniziale; i < elemento_iniziale + qta_elementi; i++)
    {

        if (vettore[i] < minimo)
        {

            minimo = vettore[i];
        }
    }

    *buffer = minimo;

}

void padre(int *buffer,
           int sem_id)
{

     /* TBD: aggiungere dentro questa funzione delle chiamate a
     *      Wait_Sem() e Signal_Sem() per realizzare lo schema
     *      produttore-consumatore con buffer singolo */

    int minimo = INT_MAX;

    for (int i = 0; i < NUM_PROCESSI; i++)
    {
        if( *buffer < minimo ) {

            minimo = *buffer;
        }
    }

    /* Attesa terminazione processi figli */

    /* TBD: Utilizzare wait() per attendere la terminazione dei 10 figli */
    

    /* Risultato finale */

    printf("Il valore minimo è: %d\n", minimo);
}
