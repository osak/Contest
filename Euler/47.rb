#!/usr/bin/ruby

require 'util.rb'

$primes = prime_list(10000);
$isprime = Hash.new;
$primes.each { |p|
	$isprime[p] = true;
}

def factor_cnt(num)
	cnt = 0;
	n = num;
	$primes.each { |p|
		if $isprime[n] then
			cnt += 1;
			break;
		end
		if n % p == 0 then
			n/=p while n%p == 0;
			cnt += 1;
		end
		break if n == 1;
	}
	return cnt;
end

seq = 0;
limit_num(1, $primes[-4,4].inject(1){|r,i| r*i}) { |n|
	f = factor_cnt(n);
	if f == 4 then
		seq += 1;
		if seq == 4 then
			p n;
			exit;
		end
	else
		seq = 0;
	end
	p n if n % 1000 == 0
}

