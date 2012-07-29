require 'prime'

n = gets.to_i
knights = gets.split.map(&:to_i)
divs = (1..n).to_a.select{|v| n%v == 0}.select{|v| v <= n/3}

divs.each do |i|
	if n % i == 0
		(0..(i-1)).each do |start|
			ok = true
			pos = start
			(n/i).times do
				if knights[pos] == 0
					ok = false
					break
				end
				pos = (pos+i) % n
			end
			if ok
				puts "YES"
				exit
			end
		end
	end
end
puts "NO"
