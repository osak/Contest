#!/usr/bin/ruby

arr = Array.new;
for a in 2..100 do
	for b in 2..100 do
		arr.push(a**b);
	end
end

puts arr.uniq.size;
