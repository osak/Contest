#!/usr/bin/perl

$/ = ',';
while(<>) {
    s/^\"(\w+)\".*$/$1/;
    push @a, $_;
    #print "$_\n";
}
print "Loaded.\n";
@b = sort @a;

print "Sorted.\n";
$sum = 0;
$index = 1;
for $n(@b) {
    $score = 0;
    print "$n\n";
    for $c($n =~ /./g) {
        $score += ord($c)-ord('A')+1;
    }
    $sum += $score * $index;
    $index++;
}

print $sum;
