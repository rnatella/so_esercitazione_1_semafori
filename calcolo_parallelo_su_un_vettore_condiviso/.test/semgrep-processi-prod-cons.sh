#!/bin/bash

cd "$(dirname "$0")"

SOURCE=../processi-prod-cons.c
CONFIG=./processi-prod-cons.yml

PREPROCESSOR=../../.test/preprocessor.pl
PREPROCESSED="/tmp/"$(basename $SOURCE .c)".preprocessed.c"

cp $SOURCE $PREPROCESSED

$PREPROCESSOR $PREPROCESSED

semgrep --error --config $CONFIG $PREPROCESSED
