#!/usr/bin/ruby

gets.to_i.times do
  n = gets.to_i
  arr = gets.chomp.split.map(&:to_i)

  ans = 0
  min = nil
  arr.each do |g|
    if min.nil?
      min = g
    else
      min = g if g < min
      diff = g - min
      ans = diff if diff > ans
    end
  end

  if ans == 0
    ans = "UNFIT"
  end

  puts ans
end
