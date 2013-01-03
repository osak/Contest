#!/usr/bin/ruby

puts "300 #{300*299/2}"
(1..300).each do |a|
  ((a+1)..300).each do |b|
    puts "#{a} #{b}"
  end
end

