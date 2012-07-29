#!/usr/bin/ruby

n = gets.to_i
arr = gets.split
arr.map!(&:to_i).sort!.uniq!

ok = true
arr.each_with_index do |elem, idx|
	break if idx == arr.size-1
	ok = false if 2*elem > arr[idx+1]
end
puts ok ? "NO" : "YES"
