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

$checker = [
	[1.0/2, 1.0/2],
	[1,0],
	[3.0/2, -1.0/2],
	[2,-1],
	[5.0/2, -3.0/2],
	[3, -2],
];


def find_next(num, narr, flag)
	if flag.all? then
		return if narr[0]/100 != num % 100;
		p narr;
		p narr.inject(0) { |r,i| r+i }
		exit;
	end
	start = (num%100)*100;
	finish = start+99;
	return if start < 1000;

	(start..finish).each { |n|
		flag.each_with_index{ |f, idx|
			next if f;
			if polygonal_checker($checker[idx][0], $checker[idx][1], n) then
				tmp = flag.dup;
				tmp[idx] = true;
				find_next(n, narr+[n], tmp);
			end
		}
	}
end

flag = Array.new(5, false);
1000.times { |n|
	oct = n*(3*n-2);
	next if oct < 1000;
	break if oct > 10000;
	find_next(oct, [oct], flag);
}
