#!/usr/bin/ruby

str = gets.chomp
cnt = str.each_char.to_a.uniq.size
if cnt.even?
    puts "CHAT WITH HER!"
else
    puts "IGNORE HIM!"
end
