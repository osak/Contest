#!/usr/bin/ruby

n = gets.to_i
size = n
(0..3).each do |i|
  size |= (size>>(1<<i))
end
size ^= size>>1
size <<= 1 if size != n
ans = []

# Up-Sweep
step = 2
while step <= size
  arr = []
  (1..size/step).each do |i|
    cur = i*step
    arr << "#{cur-step/2}+#{cur}=#{cur}" if cur <= n
  end
  ans << arr if arr.size > 0
  step <<= 1
end

# Down-Sweep
step >>= 1
while step >= 2
  arr = []
  (1..size/step).each do |i|
    cur = i*step-step/2
    arr << "#{cur-step/2}+#{cur}=#{cur}" if cur <= n && cur-step/2 > 0
  end
  ans << arr if arr.size > 0
  step >>= 1
end

puts ans.size
ans.each do |arr|
  puts "#{arr.size} #{arr.join(' ')}"
end
