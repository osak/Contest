#!/usr/bin/ruby

w = 10000
l = 50000
a = Array.new(1000){rand(100)}
if a.inject(0){|acc,val| acc + val**2}*Math::PI*5 >= w*l
  puts "Incorrect"
  exit
end
puts 1
puts "#{a.size} #{w} #{l}"
puts a.join(" ")
