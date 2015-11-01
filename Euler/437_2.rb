#!/usr/bin/env ruby

require 'prime'
require 'memoize'
include Memoize

def negpow(x)
  x.odd? ? -1 : 1
end

# Calculate jacobi symbol (a/n)
def jacobi(a, n)
  if a == 0
    n == 1 ? 1 : 0
  elsif a.odd?
    negpow((a-1)*(n-1)/4) * jacobi(n%a, a)
  else
    negpow((a**2-1)/8) * jacobi(a/2, n)
  end
end
memoize :jacobi

def fastpow(a, x, mod)
  res = 1
  ord = a
  while x > 0
    if x.odd?
      res *= ord
      res %= mod
    end
    ord *= ord
    ord %= mod
    x /= 2
  end
  res
end

sum = 0
cnt = 0
Prime.each(100_000_000) do |pr|
  next if pr == 2
  a = 1 + fastpow(4, pr-2, pr)
  if jacobi(a, pr) == 1
    sum += pr
    cnt += 1
    puts "#{pr} #{sum}" if cnt % 1000 == 0
  end
end

puts cnt
puts sum
