#!/usr/bin/env ruby

n, k = gets.split.map(&:to_i)
arr = gets.split.map(&:to_i) #sorted
p arr.count{|i| i >= arr[k-1] && i > 0}
