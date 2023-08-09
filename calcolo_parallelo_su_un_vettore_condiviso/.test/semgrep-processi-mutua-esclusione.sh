#!/bin/bash

cd "$(dirname "$0")"

SOURCE=../processi-mutua-esclusione.c
CONFIG=./processi-mutua-esclusione.yml

PREPROCESSOR=../../.test/preprocessor.pl
PREPROCESSED="/tmp/"$(basename $SOURCE .c)".preprocessed.c"

cp $SOURCE $PREPROCESSED

$PREPROCESSOR $PREPROCESSED

semgrep --error --config $CONFIG $PREPROCESSED
