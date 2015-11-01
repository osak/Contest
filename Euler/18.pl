#!/usr/bin/perl

while(<>) {
    push @a, $_;
}

for $line(@a) {
    @nums = split / /, $line;
    for($i = 0; $i < @nums; $i++) {
        my $max = ($prev[$i-1] > $prev[$i]) ? $prev[$i-1]:$prev[$i];
        $curr[$i] = $max + $nums[$i];
        #printf "%d\n", $curr[$i];
    }
    @prev = @curr;
}

$max = 0;
for $n(@curr) {
    $max = $n if $n > $max;
}
print $curr[0];
