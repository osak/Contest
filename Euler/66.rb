#!/usr/bin/ruby

require 'util.rb'

def square?(num)
	s = Math.sqrt(num).to_i;
	return (s**2 == num || (s+1)**2 == num)
end

maxx = 0;
ans = 0;
(2..1000).each { |d|
	next if square?(d);

	p d
	infinite_num(1) { |i|
		x = i*i*d+1;
		if square?(x) then
			puts "("+Math.sqrt(x).to_s+")";
			if x > maxx then
				maxx = x;
				ans = d;
			end
			break;
		end
	}
}

p ans;
