#!/usr/bin/ruby

# それぞれの数字を指定されたものに置換して数を再構成する．
# たとえば 0 2 1 3 4 5 6 7 8 9 だったら
# 元の数の 1 を 2 に，2 を 1 に置換した数をキーとしてソートする．

nums = gets.split.map(&:to_i)
rank = Array.new(10)
nums.each_with_index do |n, ord|
  rank[n] = ord
end

n = gets.to_i
arr = []
n.times do
  v = gets.chomp
  tag = 0
  ord = 1
  v.each_char.reverse_each do |ch|
    tag += rank[ch.to_i]*ord
    ord *= 10
  end
  arr << [tag, v]
end
arr.sort_by{|v| v[0]}.each do |val|
  puts val[1]
end
