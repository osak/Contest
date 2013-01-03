#!/usr/bin/env ruby

t = gets.to_i
t.times do
  n = gets.to_i
  arr = gets.split.map(&:to_i)
  arr.sort!
  ans = nil
  (1...arr.size).each do |idx|
    diff = arr[idx] - arr[idx-1]
    if ans.nil? || diff < ans
      ans = diff
    end
  end
  p ans
end
