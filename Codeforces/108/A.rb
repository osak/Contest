#!/usr/bin/env ruby

n, m = gets.split.map(&:to_i)

highest = Array.new(m, 0)
list = []
n.times do
  arr = gets.chomp.each_char.to_a.map(&:to_i)
  arr.each_with_index do |score, idx|
    highest[idx] = [score, highest[idx]].max
  end
  list << arr
end

ans = 0
list.each do |arr|
  arr.each_with_index do |score, idx|
    if highest[idx] == score
      ans += 1
      break
    end
  end
end

p ans
