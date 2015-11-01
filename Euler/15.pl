#!/usr/bin/perl

$a = $b = 1;
for $n(1..20) {
    $a *= $n;
    $b *= 40-$n+1;
}

printf "%s\n", $b/$a;
