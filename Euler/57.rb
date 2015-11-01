#!/usr/bin/ruby

frac = [1,2];
cnt = 0;
1000.times { 
	frac[0] += 2*frac[1];
	frac.reverse!;
	if (frac[0]+frac[1]).to_s.length > frac[1].to_s.length then
		cnt += 1;
	end
	p frac
}
p cnt;
