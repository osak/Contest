#!/usr/bin/perl

@table = ();
$hash{2} = 2;
$hash{3} = 4;
$tmp = \%hash;
$table[0] = $tmp;
%hhh = %$tmp;
print "$hhh{2}\n";

$h = $table[0];
%ha = \$table[0];
printf "%s: $h\n", ref $h;
print "$h->{2}\n";
