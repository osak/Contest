#!/usr/bin/ruby

n, k = gets.split.map(&:to_i)
arr = []
n.times do
  p, t = gets.split.map(&:to_i)
  arr << [p, t]
end
arr.sort!{|a,b| a[0]!=b[0] ? a[0]<=>b[0] : b[1]<=>a[1]}
arr.reverse!
p arr.count(arr[k-1])
