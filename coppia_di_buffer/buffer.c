#include "buffer.h"

#include <unistd.h>
#include <stdio.h>

void produzione(int sem_id, buffer *buf1, buffer *buf2, int valore)
{

    /* TBD: Sincronizzazione per inizio produzione */

    if (buf1->stato == /* TBD */)
    {
        /* TBD: Porre il buffer 1 nello stato "in uso" */

        printf("[%d] In produzione su buf1...\n", getpid());

        sleep(1);

        buf1->valore = valore;

        /* TBD: Porre il buffer 1 nello stato "occupato" */

        printf("[%d] Prodotto il valore %d su buf1\n", getpid(), valore);
    }
    else
    {

        /* se il programma è arrivato a questo punto, vi
         * deve essere almeno uno spazio disponibile, e
         * quello spazio non è in "buf1", per cui "buf2"
         * è necessariamente libero.
         */

        /* TBD: Porre il buffer 2 nello stato "in uso" */

        printf("[%d] In produzione su buf2...\n", getpid());

        sleep(1);

        buf2->valore = valore;

        /* TBD: Porre il buffer 2 nello stato "occupato" */

        printf("[%d] Prodotto il valore %d su buf2\n", getpid(), valore);

    }

    /* TBD: Sincronizzazione per fine produzione */
}

int consumazione(int sem_id, buffer *buf1, buffer *buf2)
{

    int valore;

    /* TBD: Sincronizzazione per inizio consumazione */


    if (buf1->stato == /* TBD */)
    {
        /* TBD: Porre il buffer 1 nello stato "in uso" */

        printf("[%d] In consumazione su buf1...\n", getpid());

        sleep(2);

        valore = buf1->valore;

        /* TBD: Porre il buffer 1 nello stato "libero" */

        printf("[%d] Consumato il valore %d su buf1\n", getpid(), valore);

    }
    else
    {
        /* se il programma è arrivato a questo punto, vi
         * deve essere almeno un messaggio disponibile, e
         * quel messaggio non è in "buf1", per cui "buf2"
         * è necessariamente occupato.
         */

        /* TBD: Porre il buffer 2 nello stato "in uso" */

        printf("[%d] In consumazione su buf2...\n", getpid());

        sleep(2);

        valore = buf2->valore;

        /* TBD: Porre il buffer 2 nello stato "libero" */

        printf("[%d] Consumato il valore %d su buf2\n", getpid(), valore);

    }

    /* TBD: Sincronizzazione per fine consumazione */

    return valore;
}
