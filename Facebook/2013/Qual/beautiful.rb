#!/usr/bin/ruby

def solve
  gets.to_i.times do |i|
    res = yield
    puts "Case ##{i+1}: #{res}"
  end
end

solve do
  str = gets.chomp.downcase
  arr = str.each_char.select{|c| ("a".."z").include?(c)}.to_a.sort.chunk{|c| c}.map{|ch,lst| [ch,lst.size]}
  score = 0
  arr.sort_by!{|e| e[1]}.reverse.each_with_index do |e, idx|
    score += (26-idx) * e[1]
  end
  score
end
