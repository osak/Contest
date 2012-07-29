#!/usr/bin/ruby

def solve(n, a, b)
    fuel = a[0]
    arr = [fuel]
    (n-1).times { |i|
        fuel -= b[i]
        arr << fuel
        fuel += a[i+1]
    }
    min = arr.min
    ret = []
    if min >= 0
        ret << 1
        min = 0
    end
    arr.each_with_index { |v, i|
        ret << i+1 if v == min
    }
    ret
end

n = gets.to_i
a = gets.split.map(&:to_i)
b = gets.split.map(&:to_i)
b_rev = b.reverse
b_rev = b_rev[1..-1] + [b_rev[0]]
a1 = solve(n, a, b)
a2 = solve(n, a.reverse, b_rev).map{|v| n+1-v}
ans = (a1+a2).sort.uniq
puts "#{ans.size}\n#{ans.join(' ')}"
