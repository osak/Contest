#!/usr/bin/ruby

require 'util.rb'

infinite_num(1) { |n|
	digits = n.to_s.scan(/./).sort;
	ok = true;
	for i in 2..6 do
		d = (n*i).to_s.scan(/./).sort;
		if digits != d then
			ok = false;
			break;
		end
	end
	if ok then
		p n;
		exit;
	end
}

