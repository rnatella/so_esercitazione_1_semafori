#!/bin/bash

source $(dirname "$0")/../../.test/test.sh

BINARY=main_padre
OUTPUT=/tmp/output.txt
TIMEOUT=30
SKIPPED=0


init_feedback "Esercizio lettori-scrittori"


compile_and_run $BINARY $OUTPUT $TIMEOUT


perl -n -e 'BEGIN { $val1=0; $val2=0; }  if(/Scrittura\sbuffer:\sval1=(\d+),\sval2=(\d+)/) { $val1=$1; $val2=$2; }  if(/Lettura\sbuffer:\sval1=(\d+),\sval2=(\d+)/) { if($1!=$val1 || $2!=$val2) { exit(1); } }' $OUTPUT

if [ $? -ne 0 ]
then
    failure "L'esecuzione non accede al buffer in ordine corretto"
fi


static_analysis


success


