#!/usr/bin/env ruby

def rec(i, j, k)
	p i
	rec(i+1, j, k)
end

rec(1, 2, 3)
