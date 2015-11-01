#!/usr/bin/perl

@num = (1);

for $n(1..100) {
    for($i = 0; $i < @num; $i++) {
        $num[$i] *= $n;
    }
    for($i = 0; $i < @num; $i++) {
        if($num[$i] >= 10) {
            $num[$i+1] += int($num[$i]/10);
            $num[$i] %= 10;
        }
    }
    $i = @num;
    while($num[$i] > 10) {
        $num[$i+1] += int($num[$i]/10);
        $num[$i] %= 10;
        $i++
    }
}

$sum = 0;
for $n(@num) {
    $sum += $n;
}

print $sum;
