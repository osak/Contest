#!/usr/bin/env ruby

# 愚直に計算する。

PANDIGITAL = ('1'..'9').to_a.freeze
HEAD_A = 10**9
TAIL_A = 10**9
def check(n, ord)
  head = (n / (ord / HEAD_A)).to_s.chars.sort
  tail = (n % TAIL_A).to_s.chars.sort
  head == PANDIGITAL and tail == PANDIGITAL
end

a, b = 1, 1
ord = 10
k = 2
loop do
  a, b = b, a+b
  if b >= ord
    ord *= 10
  end
  k += 1
  if k >= 541
    if check(b, ord)
      puts b
      puts k
      break
    end
  end
  if k % 1000 == 0
    puts k
  end
end

