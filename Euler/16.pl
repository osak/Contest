#!/usr/bin/perl

@num = (1);
for(1..1000) {
    for($i = 0; $i < @num; $i++) {
        $num[$i] *= 2;
    }
    for($i = 0; $i < @num; $i++) {
        if($num[$i] >= 10) {
            $num[$i+1] += int($num[$i] / 10);
            $num[$i] %= 10;
        }
    }
}
$sum = 0;
for $a(@num) {
    $sum += $a;
}
print "$sum\n";
