#!/usr/bin/perl

@primes = ();

$num = shift;
for($i = 3; ; $i += 2) {
    $isprime = true;
    for $n(@primes) {
        if($i % $n == 0) {
            $isprime = false;
            last;
        }
    }
    next unless $isprime;

    if($num % $i == 0) {
        printf "%d * %d\n", $i, $num/$i;
        last;
    }
    push @primes, $i;
}
