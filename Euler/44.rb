#!/usr/bin/ruby

pentagonal = Array.new;
ispentagonal = Hash.new;

for i in 1..3000 do
	p = i*(3*i-1)/2;
	pentagonal.push(p);
	ispentagonal[p] = true;
end

pentagonal.each { |m|
	pentagonal.each { |j|
		break if j > m;
		sum = m+2*j;
		break if sum > pentagonal.last;
		if ispentagonal[sum] && ispentagonal[sum-j] then
			puts "#{j} #{sum} #{m}";
			exit;
		end
	}
}
