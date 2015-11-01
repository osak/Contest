#!/usr/bin/ruby

primes = Array.new;
primes.push(2);
isprime = Array.new(1000000,false);
isprime[2] = true;

for i in 1..500000 do
	n = i*2+1;
	puts "Process #{n}" if i % 100000 == 0;
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
	end
end

puts "end prime #{primes.size}"

sum = 0;
primes.each { |p|
	next if p.to_s.count('024568') != 0;
	str = p.to_s;
	ok = true;
	(p.to_s.length-1).times {
		str = str[1..-1]<<str[0];
		if !isprime[str.to_i] then
			ok = false;
			break;
		end
	}
	if ok then
		puts p;
		sum += 1;
	end
}

puts sum;
