# Name: Little Pony and Crystal Mine
# Level: 1
# Category: 実装,Implementation
# Note:

n = gets.to_i

arr = []
(n/2).times do |r|
  l = ("D" * (r+1)).rjust((n+1)/2, "*")
  arr << l + l.reverse[1..-1]
end

puts arr
puts "D" * n
puts arr.reverse
