#!/usr/bin/ruby

digits = 1;
total = 0;
ans = 1;
next_total = 10;
while true do
	tmp = total + digits*((10**digits)-1-(10**(digits-1)-1));
	if tmp > next_total then
		#この桁数での何番目か？(0 origin)
		d = next_total - total - 1;
		num = 10**(digits-1) + d/digits;
		ans *= num.to_s[d%digits].chr.to_i;
		break if next_total == 1000000;
		next_total *= 10;
		redo;
	end
	total = tmp;
	puts total;
	digits += 1;
end

puts ans;
