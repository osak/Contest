#!/usr/bin/perl

$p1 = 1;
$p2 = 2;
$sum = 2;
while(1) {
    $fib = $p1+$p2;
    last if $fib >= 4000000;
    if($fib % 2 == 0) {
        $sum += $fib;
    }
    $p1 = $p2;
    $p2 = $fib;
}

print "$sum\n";
