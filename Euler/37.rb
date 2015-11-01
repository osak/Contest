#!/usr/bin/ruby

primes = Array.new;
primes.push(2);
isprime = Array.new(1, false);
isprime[2] = true;

sum = 0;
cnt = 0;
n = 3;
while true do
	ok = true;
	root = Math.sqrt(n);
	primes.each { |p|
		break if p > root;
		if n % p == 0 then
			ok = false;
			break;
		end
	}
	if ok then
		primes.push(n);
		isprime[n] = true;
		#check is it trunctable
		if n > 10 then
			trunctable = true;
			str = n.to_s;
			while str != '' do
				if !isprime[str.to_i] then
					trunctable = false;
					break;
				end
				str = str[1..-1];
			end
			if trunctable then
				str = n.to_s;
				while str != '' do
					if !isprime[str.to_i] then
						trunctable = false;
						break;
					end
					str.chop!;
				end
				if trunctable then
					sum += n;
					puts n;
					cnt += 1;
					if cnt == 11 then
						puts sum;
						exit;
					end
				end
			end
		end
	end

	n += 2;
end
