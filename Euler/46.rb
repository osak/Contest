#!/usr/bin/ruby

def infinite_odd
	n = 3;
	while true do
		yield n;
		n += 2;
	end
end

primes = Array.new;
isprime = Hash.new;
primes.push(2);
isprime[2] = true;

infinite_odd { |n|
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
		primes.push(n);
		isprime[n] = true;
	else
		goldbach = false;
		for i in 1..root do
			if isprime[n-2*i*i] then
				goldbach = true;
				break;
			end
		end
		if !goldbach then
			p n
			exit;
		end
	end

	p n if n%10000 == 1;
}
