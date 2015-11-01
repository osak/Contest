#!/usr/bin/ruby

sum = 0;
for i in 1..1001 do
	next if i % 2 == 0;
	#右上に向かう列
	sum += i*i;
	#右下に向かう列
	sum += i*i+i+1 if i < 1001;
	#左下に向かう列
	sum += i*i+(i+1)*2 if i < 1001;
	#左上に向かう列
	sum += i*i+(i+1)*3 if i < 1001;
end

puts sum;

