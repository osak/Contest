#!/usr/bin/ruby

#2桁*3桁=4桁のみあり得る
#まちがい。1桁*4桁=4桁も。
r = Hash.new
sum = 0;
for i in 1..99 do
	next if i.to_s.index('0') != nil;
	a1 = i.to_s.scan(/./);
	next if a1.size != a1.uniq.size;
	for j in 100..9999 do
		next if j.to_s.index('0') != nil;
		a2 = j.to_s.scan(/./);
		next if a2.size != a2.uniq.size;
		k = i*j;
		next if k.to_s.index('0') != nil;
		a3 = k.to_s.scan(/./);
		a4 = a1+a2+a3;
		if a4.size == 9 && a4.uniq.size == 9 then
			if r[k] == nil then
				puts "#{i} * #{j} = #{k}";
				sum += k;
				r[k] = true;
			end
		end
	end
end

puts sum;
