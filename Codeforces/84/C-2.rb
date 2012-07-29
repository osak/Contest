#!/usr/bin/ruby

n = gets.to_i
seven = (n/7)
while true
	if (n-seven*7) % 4 == 0
		puts '4'*((n-seven*7)/4) << '7'*seven
		exit
	end
	seven -= 1
	if seven == -1
		puts -1
		exit
	end
end
