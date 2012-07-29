#!/usr/bin/env ruby

gets.to_i.times do |cases|
    n = gets.to_i
    len = n.to_s(2).length
    k = 2**(len-1)-1
    rem = n - k

    ans = k.to_s(2).count('1') + rem.to_s(2).count('1')
    puts "Case ##{cases+1}: #{ans}"
end
