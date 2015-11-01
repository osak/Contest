#!/usr/bin/perl

$table[0] = 0;
$table[1] = 1;
sub calc_chain($) {
    my $start = shift;

#It's too big...
    if($start > 1000000) {
        my $cnt = 1;
        while($start > 1000000) {
            if($start % 2 == 0) {
                $start /= 2;
            }
            else {
                $start *= 3;
                $start++;
            }
            $cnt++;
        }

        return calc_chain($start)+$cnt;
    }
    elsif(!defined $table[$start]) {
        if($start % 2 == 0) {
            $table[$start] = calc_chain($start/2);
        }
        else {
            $table[$start] = calc_chain($start*3+1);
        }
    }
    return $table[$start] + 1;
}

$maxlen = 0;
$maxnum = 0;
for($n = 1; $n < 1000000; $n++) {
    $len = calc_chain($n);
    if($len > $maxlen) {
        $maxlen = $len;
        $maxnum = $n;
        printf "%d produces %d length chain.\n", $maxnum, $maxlen;
    }
}

