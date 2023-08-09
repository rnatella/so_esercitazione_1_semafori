#!/bin/bash

ipcclean() {
    ipcs -q | awk '($$2~/^[0-9]+$$/) { system("ipcrm -q " $$2) }'
    ipcs -m | awk '($$2~/^[0-9]+$$/) { system("ipcrm -m " $$2) }'
    ipcs -s | awk '($$2~/^[0-9]+$$/) { system("ipcrm -s " $$2) }'
}

failure() {
    echo "Esecuzione fallita"
    ipcclean
    exit 1
}

cd "$(dirname "$0")"

BINARY=../minimo-prod-cons
OUTPUT=/tmp/minimo.txt


if [ ! -e $BINARY ]
then
    failure
fi


rm -f $OUTPUT

if ! $BINARY > $OUTPUT;
then
    failure
fi


ipcclean

IPC_BEFORE=$(ipcs | grep -c "0x")

if ! ../minimo-mutua-esclusione > $OUTPUT;
then
    failure
fi

IPC_AFTER=$(ipcs | grep -c "0x")

if [[ $IPC_BEFORE != $IPC_AFTER ]]
then
    failure
fi


PROCESSI=$(grep -F -c "[FIGLIO] Il minimo locale è" $OUTPUT)

if [[ $PROCESSI != 10 ]]
then
    failure
fi

for I in 0 1000 2000 3000 4000 5000 6000 7000 8000 9000 1000
do
    if ! grep -F "Ricerca del minimo: elementi da ${I} a "$(($I+999)) $OUTPUT;
    then
        failure
    fi
done

MINIMO_FIGLI=$(grep -F "[FIGLIO] Il minimo locale è " $OUTPUT | awk '{print $NF}' | sort -n | head -1)
MINIMO_PADRE=$(grep -F "[PADRE] Il valore minimo assoluto è" $OUTPUT | awk '{print $NF}')

if [[ $MINIMO_FIGLI != $MINIMO_PADRE ]]
then
    failure
fi

