#!/usr/bin/ruby

factorial = Array.new
for i in 1..10 do
	f = 1;
	for j in 1..i do
		f *= j;
	end
	factorial[i] = f;
end
factorial[0] = 1;
p factorial;

nums=[0,1,2,3,4,5,6,7,8,9];
remain = 1000000-1;
num = 0;

10.times { |i|
	idx = remain / factorial[9-i];
	num *= 10;
	num += nums[idx];
	nums.delete_at(idx);
	remain %= factorial[9-i];
}

puts num;
