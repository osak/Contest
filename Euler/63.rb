#!/usr/bin/ruby

cnt = 0;
(1..9).each { |n|
	(1..1000).each { |p|
		num = n**p;
		len = num.to_s.length;
		cnt += 1 if len == p;
		break if p-len >= 2;
	}
}
p cnt
