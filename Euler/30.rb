#!/usr/bin/ruby

sum = 0;
for i in 2..300000 do
	s = 0;
	i.to_s.each_byte { |c|
		c -= '0'[0];
		s += c**5;
	}
	if s == i then
		puts i;
		sum += i;
	end
end
puts sum;

