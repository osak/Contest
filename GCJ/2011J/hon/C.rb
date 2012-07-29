#!/usr/bin/env ruby

gets.to_i.times do |case_num|
	s1 = gets.chomp
	s2 = gets.chomp
	
	ans = 'zzzzzzzzzz'
	(2**s1.length).times do |pat|
		str = s1.dup
		s1.length.times do |pos|
			str[pos] = '*' if pat[pos] == 0
		end
		str.gsub!(/\*+/, '*')
		reg = Regexp.new('^' + str.gsub('*', '.*') + '$')
		if reg.match(s1) && !reg.match(s2)
			if ans.length > str.length
				ans = str
			elsif ans.length == str.length
				as = ans.count('*')
				ss = str.count('*')
				if as > ss || (as == ss && ans > str)
					ans = str
				end
			end
		end
	end

	puts "Case ##{case_num+1}: #{ans}"
end

