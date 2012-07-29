#!/usr/bin/ruby

LIM = 1000000000
fibs = [0,1]
a = 0
b = 1
loop do
  f = a+b
  break if f > LIM
  fibs << f
  a,b = b,f
end

dict = {}
fibs.each do |f|
  dict[f] = true
end

n = gets.to_i
ans = "I'm too stupid to solve this problem"
catch(:found) do 
  (0...fibs.size).each do |ai|
    (ai...fibs.size).each do |bi|
      rem = n - fibs[ai] - fibs[bi]
      if dict[rem]
        ans = [fibs[ai],fibs[bi],rem].sort.join(" ")
        throw :found
      end
    end
  end
end

puts ans
