#!/usr/bin/perl

@table = ();

sub sumdivisor($) {
    my $num = shift;
    if(!defined $table[$num]) {
        $limit = $num/2;
        for($i = 1; $i < $limit; $i++) {
            if($num % $i == 0) {
                $table[$num] += $i;
                $table[$num] += $num/$i if $i!=1;
                $limit = $num/$i;
            }
        }
    }
    return $table[$num];
}

$sum = 0;
printf "%d\n", sumdivisor(220);
for $n(1..10000) {
    $s1 = sumdivisor($n);
    $s2 = sumdivisor($s1);
    if($s2 == $n and $s1 != $n) {
        $sum += $s1;
        printf "%d and %d are amicable.\n", $s1, $s2;
    }
}

printf "%d\n", $sum;
