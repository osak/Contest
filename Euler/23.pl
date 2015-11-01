#!/usr/bin/perl

sub isabundant($) {
    my $num = shift;
    if(!defined $abundant[$num]) {
        my $limit = $num;
        my $sum = 0;
		my $root = sqrt($num);
        for(my $i = 1; $i < $limit; $i++) {
            if($num % $i == 0) {
                $sum += $i;
                $sum += $num / $i if $i != 1 && $i != $root;
                last if $sum > $num;
                $limit = $num/$i;
            }
        }
        $abundant[$num] = ($sum > $num);
    }

    return $abundant[$num];
}

my $sum = 0;
for my $n(1..28123) {
    my $ok = 1;
    for(my $i = 1; $i < $n/2; $i++)  {
        if(isabundant($i) && isabundant($n-$i)) {
            $ok = 0;
			last;
        }
    }

    if($ok) {
        $sum += $n;
        #printf "%d\n", $n;
    }
    if($n % 1000 == 0) {
        printf "done %d\n", $n;
    }
}

print $sum;
