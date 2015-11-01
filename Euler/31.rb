#!/usr/bin/ruby

$coin = [200,100,50,20,10,5,2,1];

def search(price, pos)
	return 1 if $coin[pos] == 1;
	return 1 if price == 0;
	abort if price < 0;
	pat = 0;
	(price / $coin[pos]+1).times { |i|
		pat += search(price-$coin[pos]*i, pos+1);
	}
	return pat;
end

puts search(200, 0);
