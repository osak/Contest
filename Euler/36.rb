#!/usr/bin/ruby

def num2bin(num)
	fig = 2**Integer((Math.log(num)/Math.log(2)));
	str = '';
	while fig >= 1 do
		str += (num >= fig) ? '1' : '0';
		num %= fig;
		fig /= 2;
	end
	return str;
end

def palindromic?(str)
	return str == str.reverse;
end

puts num2bin(585);

sum = 0;
for n in 1..1000000 do
	next unless palindromic?(n.to_s);
	sum += n if palindromic?(num2bin(n));
end

puts sum;

