#!/usr/bin/ruby

require 'util.rb'

primes = prime_list(10000).reverse;
isprime = Hash.new;
primes.each { |p|
	isprime[p] = true;
}

primes.each { |p|
	primes.each { |p2|
		next if p2 >= p;
		p3 = p2-(p-p2);
		if isprime[p3] then
			a1 = p.to_s.scan(/./).sort;
			a2 = p2.to_s.scan(/./).sort;
			a3 = p3.to_s.scan(/./).sort;
			if a1 == a2 && a2 == a3 then
				puts "#{p} #{p2} #{p3}";
			end
		end
	}
}


