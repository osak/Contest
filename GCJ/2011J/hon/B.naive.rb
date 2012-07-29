#!/usr/bin/env ruby

gets.to_i.times do |case_num|
    a, b, c = gets.split.map(&:to_i)
    a = a**a
    if b == 2
		a = a**a
	end

    puts "Case ##{case_num+1}: #{a % c}"
end
