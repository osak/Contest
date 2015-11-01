#!/usr/bin/perl

@nums = qw(one two three four five six seven eight nine);
@tens = qw(twenty thirty fourty fifty sixty seventy eighty ninety);
@elevs = qw(ten eleven twelve thirteen fourteen fifteen sixteen seventeen eighteen nineteen);

sub num2str($) {
    my $num = shift;
    my $str = "";
    if($num >= 100) {
        $str .= $nums[int($num/100)-1] . "hundred";
        if($num % 100 != 0) {
            $str .= "and";
        }
        $num %= 100;
    }
    if($num >= 20) {
        $str .= $tens[int($num/10)-2];
        $num %= 10;
    }
    elsif($num >= 10) {
        $str .= $elevs[int($num%10)];
        $num = 0;
    }

    if($num > 0) {
        $str .= $nums[$num-1];
    }

    return $str;
}

printf "%s %d\n", num2str(473), length(num2str(101));

my $cnt = 0;
for $i(1..999) {
    my $s = num2str($i);
    $cnt += length($s);
}

printf "%d\n", $cnt+3+8;

