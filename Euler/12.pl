#!/usr/bin/perl

@primes = (2, 3);
$nextsearch = 5;
@table = ();

sub gen_prime($) {
    my $cnt = 0;
    my $max = shift;
    for(my $i = $nextsearch; $i <= $max; $i += 2) {
        my $sqrt = sqrt($i);
        my $isprime = 1;
        for $n(@primes) {
            last if $n > $sqrt;
            if($i % $n == 0) {
                $isprime = 0;
                last;
            }
        }
        next unless $isprime;

        push @primes, $i;
        $cnt++;
    }
    if($max > $nextsearch) {
        $nextsearch = $max;
        $nextsearch++ if $max % 2 == 0;
    }
}

sub get_divisorhash($) {
    my $num = shift;
    if(!defined $table[$num]) {
        my %hash;
        gen_prime($num);
        for $n(@primes) {
            while($num % $n == 0) {
                $hash{$n}++;
                $num /= $n;
            }
        }
        $table[$num] = \%hash;
    }
    return $table[$num];
}


for(my $i = 2; ; $i+=2) {
    my $hash1 = get_divisorhash($i-1);
    my $hash2 = get_divisorhash($i/2);
    my $hash3 = get_divisorhash($i+1);

    my %facs1 = (), %facs2 = ();
    while(($key, $value) = each(%$hash1)) {
        $facs1{$key} += $value;
    }
    while(($key, $value) = each(%$hash3)) {
        $facs2{$key} += $value;
    }
    while(($key, $value) = each(%$hash2)) {
        $facs1{$key} += $value;
        $facs2{$key} += $value;
    }
    
    my $cnt1 = 1;
    for $n(values(%facs1)) {
        $cnt1 *= $n+1;
    }
    my $cnt2 = 1;
    for $n(values(%facs2)) {
        $cnt2 *= $n+1;
    }
    if($cnt1 >= 500) {
        printf "%dth has %d divisors\n", $i-1, $cnt1;
        exit;
    }
    elsif($cnt2 >= 500) {
        printf "%dth has %d divisors\n", $i, $cnt2;
        exit;
    }
}

