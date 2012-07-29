#!/usr/bin/env ruby

gets.to_i.times do |case_num|
	k = gets.to_i
	es = gets.split.map(&:to_i)

	ans = 0
	sin = Math.sin(2*Math::PI / k).abs
	#puts "Org: #{es.inspect}"
	es.permutation do |perm|
		area = 0
		perm.each_with_index do |l, i|
			nl = i+1==k ? perm[0] : perm[i+1]
			area += sin * l * nl / 2
		end
		if area > ans
	#		p perm
			ans = [ans, area].max
		end
	end

	puts "Case ##{case_num+1}: #{ans}"
end
