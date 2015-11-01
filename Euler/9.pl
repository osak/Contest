#!/usr/bin/perl

for $i(1..1000) {
    for $j($i..1000) {
        if(2000*(500-$i-$j)+2*$i*$j == 0) {
            printf "%d %d %d\n", $i, $j, $i*$j*(1000-$i-$j);
            exit;
        }
    }
}
