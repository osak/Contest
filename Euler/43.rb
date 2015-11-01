#!/usr/bin/ruby

fac = [1,1,2,6,24,120,720,5040,40320,362880,3628800,3628800*11];

pat = 0;
sum = 0;
while pat < fac[10] do
	str = '';
	digits = [0,1,2,3,4,5,6,7,8,9].map{|d| d.to_s};
	p = pat;
	10.times { |i|
		pos = p / fac[9-i];
		str += digits[pos];
		digits.delete_at(pos);
		p %= fac[9-i];
	}

	primes = [2,3,5,7,11,13,17];
	ok = true;
	for i in 1..7 do
		if str[i,3].to_i % primes[i-1] != 0 then
			pat += fac[7-i];
			ok = false;
			break;
		end
	end
	if !ok then
		next;
	end
	p str;
	sum += str.to_i;
	pat += 1;
end

p sum;
