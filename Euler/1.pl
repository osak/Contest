#!/usr/bin/perl

for $n(1..999) {
    $sum += $n if ($n % 3 == 0) or ($n % 5 == 0);
}
print $sum;
