#!/usr/bin/ruby

n,k = gets.split.map(&:to_i)
arr = gets.split.map(&:to_i)

left = arr.min.to_f
right = arr.max.to_f

while right-left > 1e-6
	mid = (left+right)/2
	upper,lower = arr.partition { |v| v > mid }
	x = upper.map { |v| v - mid }.inject(&:+)
	l = lower.map { |v| v - mid }.inject(&:+)

	if l+x-x*k/100 >= 0
		left = mid
	else
		right = mid
	end
end

printf "%.7f\n", (left+right)/2
