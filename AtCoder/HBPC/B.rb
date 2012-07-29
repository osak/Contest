#!/usr/bin/env ruby

def to_min(str)
  hour, min = str.split(":").map(&:to_i)
  hour*60 + min
end

city_a = gets.chomp
names = gets.chomp.split
n = gets.to_i

graph = Hash.new{|h,k| h[k] = []}
n.times do
  city1, t1, city2, t2 = gets.chomp.split
  s1 = to_min(t1)
  s2 = to_min(t2)
  graph[city1] << [city2,s2-s1]
  graph[city2] << [city1,s1-s2]
end

diff = {}
queue = [[city_a, 0]]
until queue.empty?
  city, d = queue.shift
  diff[city] = d
  #puts "#{city} #{d}"

  graph[city].each do |edge|
    next_city, de = *edge
    next if diff.has_key?(next_city)
    queue << [next_city, d+de]
  end
end

city_b = gets.chomp
min_b = to_min(gets.chomp)
min_b -= diff[city_b]
min_b += 60*24 while min_b < 0
min_b -= 60*24 while min_b >= 60*24

hr = min_b / 60
mn = min_b % 60

puts names[hr]
