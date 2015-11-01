#!/usr/bin/perl

@primes = ();
push @primes, 2;
for($i = 3; ; $i += 2) {
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
    last if @primes == 10001;
}

printf "%d\n", $primes[-1];

