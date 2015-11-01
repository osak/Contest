#!/usr/bin/perl

$i = 123451;
$i =~ s/^(.)(.*)\1$/$2/;
print "$i\n";

$largest = 0;
for($i = 999; $i >= 100; $i--) {
    for($j = $i; $j >= 100; $j--) {
        $product = $i*$j;
        while($product =~ s/^(.)(.*)\1$/$2/) {}
        if(length($product) < 2) {
            $largest = $i*$j if $i*$j > $largest;
        }
    }
}

print "%d\n", $largest;
