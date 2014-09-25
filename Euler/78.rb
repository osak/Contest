#!/usr/bin/env ruby

# Reccurence formula of partition number
# http://en.wikipedia.org/wiki/Partition_(number_theory)#Recurrence_formula

$memo = Array.new

def calc(n)
  return 0 if n < 0
  return 1 if n == 0 || n == 1
  return $memo[n] if $memo[n]
  k = 1
  res = 0
  loop do
    penta = k * (3*k - 1)/2
    penta2 = -k * (3*-k - 1)/2
    #puts "#{n} #{penta} #{penta2}"
    break if penta > n
    if k.odd?
      res += calc(n-penta)
      res += calc(n-penta2)
    else
      res -= calc(n-penta)
      res -= calc(n-penta2)
    end
    k += 1
  end
  $memo[n] = res
end

puts calc(5)
(1..Float::INFINITY).each do |i|
  if calc(i) % 1_000_000 == 0
    puts i
  end
end
