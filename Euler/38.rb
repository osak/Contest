#!/usr/bin/ruby

largest = 123456789;

for n in 1..10000 do
	str = '';
	for i in 1..9 do
		p = n*i;
		break if p.to_s.scan(/./).uniq.size != p.to_s.size;
		break if p.to_s.index('0') != nil;
		break if str.count(p.to_s) != 0;
		str += p.to_s;
	end
	if str.length == 9 then
		if str.to_i > largest then
			largest = str.to_i;
			puts "n=#{n}, #{largest}";
		end
	end
	n += 1;
end
