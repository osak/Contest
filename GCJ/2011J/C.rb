#!/usr/bin/env ruby

gets.to_i.times do |cases|
	n = gets.to_i
	str = n.to_s(2).reverse
	dp = Array.new(str.size) { [0, 0] }
	str.size.times do |i|
		if str[i] == '0'
			# no carry -> no carry
			a = (i>0) ? dp[i-1][0] : 0
			# no carry -> carry
			b = ((i>0) ? dp[i-1][0] : 0) + 2
			# carry -> no carry
			c = -1
			# carry -> carry
			d = ((i>0) ? dp[i-1][1] : -10000) + 1

			dp[i][0] = [a, c, 0].max
			dp[i][1] = [b, d, 0].max
		else
			# no carry -> no carry
			a = ((i>0) ? dp[i-1][0] : 0) + 1
			# no carry -> carry
			b = -1
			# carry -> no carry
			c = (i>0) ? dp[i-1][1] : -10000
			# carry -> carry
			d = ((i>0) ? dp[i-1][1] : -10000) + 2

            puts "#{a} #{b} #{c} #{d}"
			dp[i][0] = [a, c, 0].max
			dp[i][1] = [b, d, 0].max
		end
	end

	puts "Case ##{cases+1}: #{dp[-1][0]}"
end
