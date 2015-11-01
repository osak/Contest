#!/usr/bin/ruby

require 'util.rb'

$limit = 10000;
$primes = prime_list($limit);
$isprime_hash = Hash.new
$primes.each { |p|
	$isprime_hash[p] = true;
}

def isprime(num)
	if $isprime_hash.has_key?(num) then
		return $isprime_hash[num];
	end

	root = Math.sqrt(num);
	isp = true;
	$primes.each { |p|
		break if p > root;
		if num % p == 0 then
			isp = false;
			break;
		end
	}
	$isprime_hash[num] = isp;
	return isp;
end

def process(arr,idx)
	if arr.size == 5 then
		p arr;
		puts arr.inject(0){|r,i| r+i}
		exit
	end

	$primes[idx..-1].each_with_index { |p,i|
		pstr = p.to_s;
		ok = true;
		arr.each { |elem|
			elemstr = elem.to_s;
			if !isprime((pstr+elemstr).to_i) || !isprime((elemstr+pstr).to_i) then
				ok = false;
				break;
			end
		}

		process(arr+[p],idx+i) if ok
	}
end

process([],0)
