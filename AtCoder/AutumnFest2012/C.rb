#!/usr/bin/ruby

n = gets.to_i
cards = gets.split.map(&:to_f)
res = cards.reduce(0){|acc,val| acc + val*(n-1)/n}
printf("%.7f\n", res)
