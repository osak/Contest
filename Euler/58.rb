#!/usr/bin/ruby

require 'util.rb'

$primes = prime_list(100000);

def isprime(num)
	root = Math.sqrt(num);
	prime = true;
	$primes.each { |p|
		break if p > root;
		if num % p == 0 then
			prime = false;
			break;
		end
	}
	return prime;
end


num = 1;
side = 3;
primecnt = 0;
while true do
	num += 1+side-2;
	primecnt += 1 if isprime(num);
	num += side-1;
	primecnt += 1 if isprime(num);
	num += side-1;
	primecnt += 1 if isprime(num);
	num += side-1;
	#これは自明に平方数なので見ない
	prime_ratio = primecnt.to_f / ((side-1)/2*4+1);
	if prime_ratio < 0.1 then
		p side;
		exit;
	end
	if num > 100000**2 then
		puts "Limit!";
		exit;
	end
	side += 2;
	p prime_ratio if side % 100 == 1;
end

