#!/usr/bin/ruby

require 'prime'

1.upto(gets.to_i) do |case_num|
    n,pd,pg = gets.chomp.split.map(&:to_i)

    possible = true
    possible = false if (pg == 100 && pd != 100) || (pg == 0 && pd != 0)

    a = 100 / 100.gcd(pd)
    b = 100 / 100.gcd(100-pd)
    possible = false if a > n || b > n || a*b/a.gcd(b) > n

    puts "Case ##{case_num}: #{possible ? "Possible" : "Broken"}"
end
