#!/usr/bin/ruby

abundant = Array.new;
prime = Array.new;
isabundant = Array.new(28123, false);

prime.push(2);
for n in 3..28123 do
	limit = Math.sqrt(n);
	ok = true;
	prime.each { |i|
		break if i > limit;
		if n % i == 0 then
			ok = false;
			break;
		end
	}
	prime.push(n) if ok;
end

for n in 1..28123 do
	#ÁÇ°ø¿ôÊ¬²ò
	factor = Array.new;
	num = n;

	sum = 1;
	prime.each { |p|
		break if p > n/2;
		a = p;
		b = 1;
		while num % p == 0 do
			b += a;
			a *= p;
			num /= p;
		end
		sum *= b;
	}
	if sum-n > n then
		abundant.push(n);
		isabundant[n] = true;
	end

	puts "Done #{n}" if n % 1000 == 0;
end

puts "Abundant numbers done.";

sum = 0;
for n in 1..28123 do
	ok = true;
	abundant.each { |i|
		break if i > n/2;
		if isabundant[n-i] then
			ok = false;
			break;
		end
	}
	if ok then
		sum += n;
	end

	puts "Done #{n}" if n % 1000 == 0;
end

p sum;

