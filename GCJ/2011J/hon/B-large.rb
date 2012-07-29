#!/usr/bin/env ruby

def modpow(x, n, m)
	tmp = x
	d = x
	res = 1
	while tmp > 0
		if tmp.odd?
			res *= d
			res %= m
		end
		d = d*d%c
		tmp >>= 1
	end
	res
end

gets.to_i.times do |case_num|
    $memo = {}
    a, b, c = gets.split.map(&:to_i)
	b.times do 
		cache = Array.new(c, -1)
		cur = a % c
		repeat_at = 0
		(1..c).each do |n|
			if cache[cur] != -1
				repeat_at = n
				break
			end
			cache[cur] = n
			cur *= a
			cur %= c
		end
		res = modpow(a, cache[cur], c*c)

    puts "Case ##{case_num+1}: #{a % c}"
end
