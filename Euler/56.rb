#!/usr/bin/ruby

ans = 0;
for a in 1..100 do
	for b in 1..100 do
		n = a**b;
		tmp = 0;
		n.to_s.scan(/./).each { |c|
			tmp += c.to_i;
		}
		ans = tmp if tmp > ans;
	end
end

p ans
