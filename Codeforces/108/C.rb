#!/usr/bin/env ruby

MOD = 1000000007
n, m = gets.split.map(&:to_i)
transpose = Array.new(m) { {} }
n.times do
  gets.chomp.each_char.to_a.each_with_index do |ch, idx|
    transpose[idx][ch] = 1
  end
end

cnt = 1
transpose.each do |set|
  cnt *= set.size
  cnt %= MOD
end

p cnt
