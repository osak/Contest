#!/usr/bin/ruby

n = gets.to_i
arr = gets.split.map(&:to_i)
ans = 0
arr.each_with_index { |v, i|
	left = right = i
	left -= 1 while left > 0 && arr[left-1] <= arr[left]
	right += 1 while right < n-1 && arr[right+1] <= arr[right]
	num = right-left+1
	ans = num if num > ans
}
puts ans
