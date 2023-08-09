#!/usr/bin/perl -pi

BEGIN {
    %defines=();
    open(SOURCE,"<", $ARGV[0]);
    while(<SOURCE>) {
        if(/#(?:define|DEFINE)\s+(\w+)\s+(.*)/) {
            $defines{$1} = $2;
        }
    }
    close(SOURCE);
}

if(!/#(?:define|DEFINE)/) {

    foreach $define (keys %defines) {

        s/$define/$defines{$define}/g;
    }
}
