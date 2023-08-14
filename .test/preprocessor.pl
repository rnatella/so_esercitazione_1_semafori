#!/usr/bin/perl

%defines=();

open(SOURCE,"+<", $ARGV[0]) or die "Opening: $!";

@SOURCE = <SOURCE>;
@NEW_SOURCE = ();

while($_ = shift @SOURCE) {

    if(/#(?:define|DEFINE)\s+(\w+)\s+(.*)/) {
        $defines{$1} = $2;
        next;
    }

    if(!/#(?:define|DEFINE)/) {

        foreach $define (keys %defines) {

            s/$define/$defines{$define}/g;
        }
    }

    if(/#(?:include|INCLUDE)\s"(.*)"/) {

        open(INCLUDE,"<",$1) or die "Opening: $!";

        @INCLUDE = <INCLUDE>;

        while($include = pop @INCLUDE) {
            unshift @SOURCE, $include;
        }

        close(INCLUDE);

        next;
    }

    push @NEW_SOURCE, $_;

}


seek(SOURCE,0,0)              or die "Seeking: $!";
print SOURCE @NEW_SOURCE      or die "Printing: $!";
truncate(SOURCE,tell(SOURCE)) or die "Truncating: $!";
close(SOURCE)                 or die "Closing: $!";

