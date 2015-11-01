#!/usr/bin/ruby

sum = 0;
for n in 1..1000 do
	sum += n**n;
end
p sum%(10**10);

