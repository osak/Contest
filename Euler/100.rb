#!/usr/bin/env ruby

# ディスクの総枚数をS, 青いディスクの枚数をXとして
#   X(X-1) / S(S-1) = 1/2
# を解く。これは変形すると
#   (2S-1)^2 - 2(2X-1)^2 = -1
# とペル方程式の形になるので、連分数展開によって解くことができる。

a1, a2, b1, b2 = 1, 1, 1, 0
loop do
  a1, a2 = 2*a1 + a2, a1
  b1, b2 = 2*b1 + b2, b1
  puts "->#{a1} #{a2}"
  if a1.odd? and b1.odd?
    s = (a1+1) / 2
    x = (b1+1) / 2
    puts "#{s} #{x}"
    if s > 1e12
      break
    end
  end
end
