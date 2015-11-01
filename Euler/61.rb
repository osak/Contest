#!/usr/bin/ruby

#Check polygonal number that written as ax^2+bx
def polygonal_checker(a,b,num)
	if b*b+4*a*num < 0 then
		false
	else
		n = (-b+Math.sqrt(b*b+4*a*num)) / (a*2);
		n.to_i.to_f == n;
	end
end

checker = [
	[1.0/2, 1.0/2],
	[1,0],
	[3.0/2, -1.0/2],
	[2,-1],
	[5.0/2, -3.0/2],
	[3, -2],
];

status = Array.new(9999-1000+1);
sum = 0;
(1000..9999).each { |num|
	s = Array.new;
	6.times { |i|
		s.push(polygonal_checker(checker[i][0], checker[i][1], num));
	}
	status[num-1000] = s;
	#p s if s.index(true)
}

1000.times { |n|
	oct = n*(3*n-2);
	next if oct < 1000;
	break if oct > 10000;

	flag = Array.new(5);

