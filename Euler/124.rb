#!/usr/bin/env ruby

# 愚直にやる。

require 'prime'

arr = []
(1..100000).each do |n|
  facts = n.prime_division
  rad = facts.reduce(1){|acc,fact| acc * fact[0]}
  arr << [rad, n]
end
arr.sort!
puts arr[10000-1][1]
