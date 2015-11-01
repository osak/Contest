#!/usr/bin/ruby

require 'util.rb'

primes = prime_list(1000000);
isprime = Hash.new;
primes.each { |p|
	isprime[p] = true;
}
puts 'end prime'

searchseq = 7;

primes.each { |p|
	pstr = p.to_s;
	for i in 0..(10-searchseq) do
		next if pstr.count(i.to_s) == 0;
		cnt = 0;
		uncnt = i;
		ok = true;
		for j in (i+1)..9 do
			s = pstr.tr(i.to_s, j.to_s);
			if isprime[s.to_i] then
				cnt += 1;
			else
				uncnt += 1;
				if uncnt >= (10-searchseq) then
					ok = false;
					break;
				end
			end
		end
		if ok && cnt == searchseq then
			puts p;
			exit;
		end
	end
}
