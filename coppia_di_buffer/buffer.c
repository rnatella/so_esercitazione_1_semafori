#include "buffer.h"

#include <unistd.h>
#include <stdio.h>

void produzione(int sem_id, buffer *buf1, buffer *buf2, int valore)
{

    buffer * buf;


    /* TBD: Il produttore deve attendere che almeno un buffer sia libero,
     *      mediante semaforo */



    /* TBD: Completare il codice che segue, per
     *      sceglire un buffer "LIBERO" (buf1 oppure buf2)
     *
     * NOTA: Non è necessario aggiungere qui la mutua esclusione
     * (MUTEX_P), poiché vi è un solo processo produttore
     */

    if (buf1->stato == /* TBD: il buf1 è libero */)
    {
        printf("[%d] In produzione su buf1...\n", getpid());

        buf = buf1;

    } else {

        printf("[%d] In produzione su buf2...\n", getpid());

        buf = buf2;
    }

    buf->stato = /* TBD: Porre il buffer nello stato "in uso" */;




    sleep(1);

    buf->valore = valore;

    buf->stato = /* TBD: Porre il buffer nello stato "occupato" */;

    printf("[%d] Prodotto il valore %d\n", getpid(), valore);



    /* TBD: Ri-attivare il consumatore, che è in attesa di un elemento da consumare */
}

int consumazione(int sem_id, buffer *buf1, buffer *buf2)
{

    buffer * buf;

    int valore;


    /* TBD: Il consumatore deve attendere che almeno un buffer sia occupato,
     *      mediante semaforo */



    /* TBD: Completare il codice che segue, per
     *      sceglire un buffer "OCCUPATO" (buf1 oppure buf2)
     *
     * NOTA: Non è necessario aggiungere qui la mutua esclusione
     * (MUTEX_C), poiché vi è un solo processo consumatore
     */

    if (buf1->stato == /* TBD: il buf1 è occupato */)
    {
        printf("[%d] In consumazione su buf1...\n", getpid());

        buf = buf1;

    } else {

        printf("[%d] In consumazione su buf2...\n", getpid());

        buf = buf2;
    }

    buf->stato = /* TBD: Porre il buffer nello stato "in uso" */;



    sleep(2);

    valore = buf->valore;

    buf->stato = /* TBD: Porre il buffer nello stato "libero" */;

    printf("[%d] Consumato il valore %d\n", getpid(), valore);


    /* TBD: Ri-attivare il produttore, che è in attesa di un buffer libero */


    return valore;
}

