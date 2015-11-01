#!/usr/bin/perl

while(<>){push@a,$_}while(@l=(pop@a)=~/\d+/g){for($i=0;$i<@l;$i++){$m[$i]=$l[$i]+($m[$i]>$m[$i+1]?$m[$i]:$m[$i+1])}}print$m[0];
