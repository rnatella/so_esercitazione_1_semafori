#include "buffer.h"

#include <unistd.h>
#include <stdio.h>

void produzione(int sem_id, buffer *buf1, buffer *buf2, int valore)
{

    buffer * buf;

    /* TBD: Sincronizzazione per inizio produzione */


    /* TBD: Completare la ricerca del buffer LIBERO */

    /* NOTA: Nel caso ci fossero stati più di un produttore,
     * sarebbe necessario qui usare la mutua esclusione
     * (MUTEX_P) per cerca il buffer LIBERO
     */

    if (buf1->stato == /* TBD */)
    {
        printf("[%d] In produzione su buf1...\n", getpid());

        buf = buf1;

    } else {

        printf("[%d] In produzione su buf2...\n", getpid());

        buf = buf2;
    }

    buf->stato = /* TBD: Porre il buffer nello stato "in uso" */;

    /* FINE RICERCA DEL BUFFER LIBERO */



    sleep(1);

    buf->valore = valore;

    /* TBD: Porre il buffer nello stato "occupato" */

    printf("[%d] Prodotto il valore %d\n", getpid(), valore);



    /* TBD: Sincronizzazione per fine produzione */
}

int consumazione(int sem_id, buffer *buf1, buffer *buf2)
{

    buffer * buf;

    int valore;

    /* TBD: Sincronizzazione per inizio consumazione */


    /* TBD: Completare la ricerca del buffer OCCUPATO */

    /* NOTA: Nel caso ci fossero stati più di un consumatore,
     * sarebbe necessario qui usare la mutua esclusione
     * (MUTEX_C) per cerca il buffer OCCUPATO
     */

    if (buf1->stato == /* TBD */)
    {
        printf("[%d] In consumazione su buf1...\n", getpid());

        buf = buf1;

    } else {

        printf("[%d] In consumazione su buf2...\n", getpid());

        buf = buf2;
    }

    buf->stato = /* TBD: Porre il buffer nello stato "in uso" */;

    /* FINE RICERCA DEL BUFFER OCCUPATO */



    sleep(2);

    valore = buf->valore;

    /* TBD: Porre il buffer nello stato "libero" */

    printf("[%d] Consumato il valore %d\n", getpid(), valore);



    /* TBD: Sincronizzazione per fine consumazione */

    return valore;
}

