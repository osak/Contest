#!/usr/bin/env ruby

gets.to_i.times do |case_num|
    $memo = {}
    a, b, c = gets.split.map(&:to_i)
    a = a**a
    if b == 2
        tmp = a
        d = a
        res = 1
        while tmp > 0
            if tmp.odd?
                res *= d
                res %= c
            end
            d = d * d % c
            tmp >>= 1
        end
        a = res
    end

    puts "Case ##{case_num+1}: #{a % c}"
end
