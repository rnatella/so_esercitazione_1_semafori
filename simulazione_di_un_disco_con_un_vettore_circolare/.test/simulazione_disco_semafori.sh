#!/bin/bash

source $(dirname "$0")/../../.test/test.sh

BINARY=programma
OUTPUT=/tmp/output.txt
TIMEOUT=240
SKIPPED=0


init_feedback "Esercizio simulazione disco, con semafori"

compile_and_run $BINARY $OUTPUT $TIMEOUT


perl -n -e 'BEGIN{$counter=0; %produced=(); %consumed=(); $ptr_testa=0; $ptr_coda=0;} if(/Richiesta\sUtente:\sposizione=(\d+),\sprocesso=(\d+)/) { push @{$produced{$2}},$1; } if(/Prelevo\srichiesta:\sposizione=(\d+),\sprocesso=(\d+)/) { push @{$consumed{$2}},$1; } if(/Produzione\sin\stesta:\s(\d+)/){ $counter++; if($1 != $ptr_testa) { exit(1); } else { $ptr_testa = ($ptr_testa + 1)%10; } } if(/Consumazione\sin\scoda:\s(\d+)/){ $counter--; if($1 != $ptr_coda) { exit(1); } else { $ptr_coda = ($ptr_coda + 1)%10; } } if($counter>10 || $counter<0) { exit(1); } END { if(scalar keys %produced != scalar keys %consumed) { exit(1); }  foreach $pid(keys %produced) { if($#{$produced{$pid}}!=$#{$consumed{$pid}}) { exit(1); }  for $i(0..$#{$produced{$pid}}) { if($produced{$pid}[$i]!=$consumed{$pid}[$i]){ exit(1); } } } }' $OUTPUT

if [ $? -ne 0 ]
then
    failure "L'esecuzione non rispetta l'ordine corretto delle produzioni e delle consumazioni"
fi


static_analysis


success


