#!/usr/bin/ruby

maxnum = 0;
maxcnt = 0;

for i in 1..999 do
	n = 1;
	cnt = 0;
	rem = Array.new;
	rem.push(n);
	while true do
		n *= 10;
		n %= i;
		cnt += 1;
		idx = rem.index(n);
		if idx != nil then
			if cnt > maxcnt then
				maxcnt = cnt-idx;
				maxnum = i;
			end
			break;
		end
		rem.push(n);
	end
end

puts maxnum;
