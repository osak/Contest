#!/usr/bin/ruby

prev = 1;
prevprev = 1;
cnt = 3;

while true do
	fib = prev+prevprev;
	prevprev = prev;
	prev = fib;
	if fib.to_s.length >= 1000 then
		puts cnt;
		exit;
	end
	cnt+=1;
end
	
