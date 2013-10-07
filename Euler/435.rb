#!/usr/bin/env ruby

# xを固定した時、n項目までの和をS_nとすると
#   [F_n    x^n    ]   [x x^2 0] [F_{n-1}x^{n-1}]
#   [F_{n-1}x^{n-1}] = [1  0  0] [F_{n-2}x^{n-2}]
#   [S_n           ]   [x x^2 1] [S_{n-1}       ]
# 右辺の行列を有限体上でN-1乗すればよい。

require_relative 'galoisfield'
require 'matrix'

MOD = (1..15).inject(&:*)
N = 10**15

ans = 0
(1..100).each do |x|
  mat = Matrix[[x, x**2, 0], [1, 0, 0], [x, x**2, 1]].map{|i| i.to_galois(MOD)}
  tmp = N-1
  cur = Matrix.identity(3).map{|i| i.to_galois(MOD)}
  pow = mat.dup
  while tmp > 0
    if tmp.odd?
      cur *= pow
    end
    pow *= pow
    tmp /= 2
  end
  ans += cur[2,0]*x + x
end
puts ans
