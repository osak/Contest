require 'prime'

arr = Prime.take_while{|i| i < 1e6.to_i}
p 100000
50000.times do |i|
  puts "3 #{arr[-(i+1)]}"
end
50000.times do |i|
  puts "4 #{arr[-(i+1)]}"
end
