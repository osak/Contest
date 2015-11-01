#!/usr/bin/ruby

#[分子,分母]
frac = [0,1];

(0..98).to_a.reverse_each { |i|
	n = (i%3 == 1 ? 2+2*(i/3) : 1);
	frac[0] += n*frac[1];
	frac.reverse!;
}
frac[0] += 2*frac[1];
p frac
sum = 0;
frac[0].to_s.scan(/./) { |c|
	sum += c.to_i;
}
p sum;
