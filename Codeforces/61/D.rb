#!/usr/bin/ruby

require 'prime'

n = gets.to_i
if n == 2
	p -1
	exit
end

arr = Prime.take(n)

n.times { |i|
	tmp = arr.dup
	tmp.delete_at(i)
	p tmp.inject(:*)
}
