#!/usr/bin/ruby

denom = 1;
numer = 1;
for a in 10..99 do
	for b in (a+1)..99 do
		next if a%10 == 0 && b%10 == 0;
		a.to_s.scan(/./).each { |ch|
			c = a.to_s.delete(ch).to_i;
			d = b.to_s.delete(ch).to_i;
			next if b == d;
			next if c*d == 0;
			#Check if a/b == c/d by check a*d == b*c
			if a*d == b*c then
				puts "#{a}/#{b}";
				numer *= a;
				denom *= b;
			end
		}
	end
end

puts "#{numer}/#{denom}";
#ユークリッドの互除法(numer > denom)
a = numer;
b = denom;
while true do
	r = a % b;
	if r == 0 then
		puts "#{numer/b} / #{denom/b}";
		exit;
	end
	a = b;
	b = r;
end
