#!/usr/bin/ruby

factorial = Array.new;
factorial[0] = 1;
for i in 1..100 do
	factorial[i] = factorial[i-1]*i;
end

cnt = 0;
for n in 1..100 do
	for r in 0..n do
		c = factorial[n]/(factorial[r]*factorial[n-r]);
		if c > 1000000 then
			cnt += 1;
		end
	end
end
p cnt;
