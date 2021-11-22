#include <unistd.h>
#include <stdio.h>

#include "buffer.h"

void leggi_buffer(buffer * b, int sem_id, int *val_1, int *val_2) {

    printf("[%d] Inizio lettura\n", getpid());

    /* TBD: Inizio lettura */


    printf("[%d] Lettura in corso: val1=%d, val2=%d\n", getpid(), b->val_1, b->val_2);

    sleep(1);

    *val_1 = b->val_1;
    *val_2 = b->val_2;


    printf("[%d] Fine lettura\n", getpid());

    /* TBD: Fine lettura */
}

void scrivi_buffer(buffer *b, int sem_id, int val_1, int val_2) {

    printf("[%d] Inizio scrittura\n", getpid());

    /* TBD: Inizio scrittura */


    printf("[%d] Scrittura in corso: val1=%d, val2=%d\n", getpid(), val_1, val_2);

    sleep(2);

    b->val_1 = val_1;
    b->val_2 = val_2;


    printf("[%d] Fine scrittura\n", getpid());

    /* TBD: Fine scrittura */
}
