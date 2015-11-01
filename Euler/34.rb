#!/usr/bin/ruby

factorial = Array.new;
for i in 1..9 do
	v = 1;
	for j in 1..i do
		v *= j;
	end
	factorial[i] = v;
end
factorial[0] = 1;

p factorial

limit = 0;
while true do
	limit += 1;
	break if factorial[9]*limit < 10**limit-1;
end
puts "limit: #{limit}";
ans = 0;
for n in 3..10**limit do
	sum = 0;
	n.to_s.scan(/./).each { |i|
		sum += factorial[i.to_i];
	}
	if sum == n then
		puts n;
		ans += n;
	end
end

