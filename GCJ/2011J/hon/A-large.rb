#!/usr/bin/env ruby

gets.to_i.times do |case_num|
	k = gets.to_i
	es = gets.split.map(&:to_i)

	ans = 0
	sin = Math.sin(2*Math::PI / k).abs
	es.sort!
	tmp = []
	es.each_with_index do |l, i|
		if i % 2 == 0
			tmp << l
		else
			tmp.unshift(l)
		end
	end

	tmp.each_with_index do |l, i|
		nl = i+1==k ? tmp[0] : tmp[i+1]
		ans += l * nl
	end

	puts "Case ##{case_num+1}: #{ans*sin / 2}"
end
