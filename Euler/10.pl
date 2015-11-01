#!/usr/bin/perl

@primes = ();
$sum = 2;
push @primes, 2;
for($i = 3; ; $i += 2) {
    last if $i > 2000000;
    $sqrt = sqrt($i);
    $isprime = 1;
    for $n(@primes) {
        last if $n > $sqrt;
        if($i % $n == 0) {
            $isprime = 0;
            last;
        }
    }
    next unless $isprime;

    push @primes, $i;
    $sum += $i;
}

printf "$sum\n";
printf "%d primes\n", scalar(@primes);

