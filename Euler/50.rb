#!/usr/bin/ruby

require 'util.rb'

primes = prime_list(1000);
seq = Array.new;
maxlen = 0;
maxp = 0;
cnt = 0;

infinite_prime { |p|
	seq.map! { |i|
		i+p;
	}
	seq.each_with_index { |i, idx|
		break if cnt-idx+1 < maxlen;
		break if i > 1000000;
		ok = true;
		primes.each { |pp|
			if i % pp == 0 then
				ok = false;
				break;
			end
		}
		if ok then
			maxlen = cnt-idx+1;
			maxp = i;
			puts "#{i} #{maxlen}"
		end
	}
	seq.push(p);
	cnt += 1;
}

