#!/bin/bash

source $(dirname "$0")/../../.test/test.sh

BINARY=minimo-prod-cons
OUTPUT=/tmp/minimo.txt
TIMEOUT=30
MAKE_RULE=$BINARY
SKIPPED=0


init_feedback "Esercizio calcolo parallelo su vettore condiviso, con produttore-consumatore"


compile_and_run $BINARY $OUTPUT $TIMEOUT $MAKE_RULE


PROCESSI=$(grep -F -c "[FIGLIO] Il minimo locale è" $OUTPUT)

if [[ $PROCESSI != 10 ]]
then
    failure "Errore nel lancio dei 10 processi figli"
fi


for I in 0 1000 2000 3000 4000 5000 6000 7000 8000 9000 1000
do
    if ! grep -F "Ricerca del minimo: elementi da ${I} a "$(($I+999)) $OUTPUT >/dev/null;
    then
        failure "Errore nei parametri passati ai processi figli (elemento iniziale, quantità elementi)"
    fi
done


MINIMO_FIGLI=$(grep -F "[FIGLIO] Il minimo locale è " $OUTPUT | awk '{print $NF}' | sort -n | head -1)
MINIMO_PADRE=$(grep -F "[PADRE] Il valore minimo assoluto è" $OUTPUT | awk '{print $NF}')

if [[ $MINIMO_FIGLI != $MINIMO_PADRE ]]
then
    failure "Errore nel calcolo del valore minimo"
fi


static_analysis $TESTDIR/processi-prod-cons.yml


success


