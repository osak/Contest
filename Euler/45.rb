#!/usr/bin/ruby

def pentagonal?(num)
	n = (1+Math.sqrt(1+2*3*4*num))/6;
	return n.to_i.to_f == n;
end

#hexagonalであれば必ずtrianguler.
n = 1;
while true do
	h = n*(2*n-1);
	if pentagonal?(h) then
		p h;
	end
	n += 1;
end
