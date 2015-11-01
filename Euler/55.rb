#!/usr/bin/ruby

isLychrel = Hash.new;
ans = 0;
for i in 1..10000 do
	n = i;
	lychrel = true;
	nums = [n];
	50.times { |cnt|
		n += n.to_s.reverse.to_i;
		nums << n;
		if isLychrel[n] || n.to_s == n.to_s.reverse then
			lychrel = false;
			break;
		end
	}
	if lychrel then
		ans += 1;
	else
		nums.each { |num|
			isLychrel[num] = true;
		}
	end
	p i if i % 1000 == 0;
end

p ans;
