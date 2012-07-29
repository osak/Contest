#!/usr/bin/ruby

6.times do |n|
	arr = (1..n).to_a
	min = max = nil
	arr.permutation do |perm|
		cost = 0
