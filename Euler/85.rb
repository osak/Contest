#!/usr/bin/env ruby

# 縦✕横 = x * w の長方形を、縦に1マス伸ばしたときに増える長方形数を考える。
# このときの増分は、増えたマスのみを使う長方形(1*wから取れる長方形)と
# x*wの長方形の中で最下段を使ったパターンを1段下に延長したものの和で表現することができる。
# 1*wを埋める長方形の取り方 a_{w1} = ∑i = w(w+1)/2 であるから
# x*w で取れる長方形数を a_{wx}, x*wで最下段を使った長方形数を b_{wx} とすると
#   b_{wx} =              a_{w1} + b_{w(x-1)}
#   a_{wx} = a_{w(x-1)} + a_{w1} + b_{w(x-1)}
#          = a_{w(x-1)} + b_{wx}
# すなわち、a_{wx}は階差数列となる。
# これを展開すると、一般項は
#   a_{wx} = a_{w1}*((x-1)^2+3(x-1)+2) / 2
# であるから、各wについて、目標値2,000,000に近くなるxの値を二分探索で求める。

TARGET = 2_000_000

def f(x)
  (x*x + 3*x + 2) / 2
end

def search(k)
  a0 = k*(k+1)/2
  left, right = 0, TARGET
  while left+1 < right
    n = (left+right) / 2
    val = a0*f(n)
    if val < TARGET
      left = n+1
    else
      right = n
    end
  end
  v1 = (a0*f(left)-TARGET).abs
  v2 = (a0*f(left+1)-TARGET).abs
  v1 < v2 ? [left, a0*f(left)] : [left+1, a0*f(left+1)]
end

cnt = 0
ans = 0
(1..TARGET).each do |i|
  x, val = search(i)
  a1 = (cnt-TARGET).abs
  a2 = (val-TARGET).abs
  if a2 < a1
    ans = i*(x+1)
    cnt = val
    puts "#{i}: #{val}, #{ans}"
  end
end
puts ans
