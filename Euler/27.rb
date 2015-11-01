#!/usr/bin/ruby

primes = Array.new;
isprime = Array.new(100000, false);
primes.push(2);
isprime[2] = true;

for n in 3..100000 do
	root = Math.sqrt(n);
	ok = true;
	primes.each { |p|
		break if p > root;
		if n % p == 0 then
			ok = false;
			break;
		end
	}
	if ok then
		primes.push(n)
		isprime[n] = true;
	end
end

puts "end prime";

maxlen = 0;
ans = 0;
for a in -1000..1000 do
	for b in primes do
		break if b > 1000;
		n = 0;
		while true do
			i = n*n + a*n + b;
			if i >= 100000 then 
				puts "i exceeds 100000!"
				exit;
			end
			break unless isprime[i];
			n += 1;
		end
		if n > maxlen then
			maxlen = n;
			ans = a*b;
		end
	end

	puts "#{a}" if a % 100 == 0;
end

puts ans
