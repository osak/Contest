#!/usr/bin/ruby

cubestr = Array.new

10000.times { |i|
	arr = (i*i*i).to_s.scan(/./).sort;
	cubestr.push([arr, i])
}

cubestr.sort!;
seq = 1;
prevarr = []
min = 10000;
cubestr.each_with_index { |a,idx|
	if prevarr == a[0] then
		seq += 1;
	else
		if seq == 5 then
			n = 10000;
			5.times { |i|
				num = cubestr[idx-i-1][1]
				n = num if num < n;
			}
			min = n if n < min;
		end
		prevarr = a[0];
		seq = 1;
	end
}

p min*min*min, min
