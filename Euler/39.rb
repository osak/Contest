#!/usr/bin/ruby

square = Array.new;

for n in 1..1000 do
	square[n] = n*n;
end

ans = 0;
maxpat = 0;
for p in 1..1000 do
	pattern = 0;
	for longest in p/3..p/2 do
		for i in 1..longest/2 do
			if square[longest] == square[i] + square[p-longest-i] then
				pattern += 1;
			end
		end
	end
	if pattern > maxpat then
		ans = p;
		maxpat = pattern;
	end
	puts p if p % 50 == 0;
end

puts ans, maxpat;
