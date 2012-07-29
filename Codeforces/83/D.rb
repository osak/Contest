#!/usr/bin/ruby

n, m, h = gets.split.map(&:to_i)
s = gets.split.map(&:to_i)

sum = s.inject(&:+)-1
subsum = sum - s[h-1] + 1

if sum < n-1
	p -1
else
	prob = 1.0
	(n-1).times { |i| prob *= (subsum-i).to_f/(sum-i) }
	p 1-prob
end
