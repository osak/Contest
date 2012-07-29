#!/usr/bin/env ruby

a, b = gets.split.map(&:to_i)

q = [[a,0]]
memo = {}
ans = nil
while !q.empty?
  cur, step = q.shift
  next if memo.has_key?(cur)
  memo[cur] = 1
  if cur == b
    ans = step
    break
  end

  [1,5,10,-1,-5,-10].each do |d|
    q << [cur+d,step+1] unless memo.has_key?(cur+d)
  end
end

puts ans
