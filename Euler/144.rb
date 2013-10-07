#!/usr/bin/env ruby

# レーザービームを起点と進行方向のベクトルで表す。
# 全反射は、このベクトルと鏡面のベクトルのなす角度Θを求め、
# 下半分の反射ではCCW, 上半分の反射ではCWにベクトルを2Θだけ回転させればよい。

class Vector
  attr_reader :x, :y
  def initialize(x, y)
    @x = x.to_f
    @y = y.to_f
  end

  def rotate!(cos)
    # assume rotate angle < PI
    sin = (1 - cos*cos)**0.5
    @x, @y = x*cos - y*sin, x*sin + y*cos
  end

  def dot(vec)
    x*vec.x + y*vec.y
  end

  def +(vec)
    Vector.new(x + vec.x, y + vec.y)
  end

  def -(vec)
    Vector.new(x - vec.x, y - vec.y)
  end

  def *(a)
    Vector.new(a*x, a*y)
  end

  def abs
    (x**2 + y**2)**0.5
  end

  def to_s
    "(#{x}, #{y})"
  end
end

vec = Vector.new(1.4-0, -9.6-10.1)
base = Vector.new(0, 10.1)
ans = 0
loop do
  a = 4*vec.x*vec.x + vec.y*vec.y
  b = 8*base.x*vec.x + 2*base.y*vec.y
  c = 4*base.x*base.x + base.y*base.y - 100
  det = b*b - 4*a*c
  k1, k2 = (-b+det**0.5)/(2*a), (-b-det**0.5)/(2*a)
  puts "#{k1}, #{k2}"

  k = k1.abs > k2.abs ? k1 : k2
  next_base = base + vec*k
  if (next_base.x.abs <= 0.01) and next_base.y > 0
    puts "exit at #{next_base}"
    break
  end

  m = -4*next_base.x/next_base.y
  puts "m=#{m}"
  mirror = Vector.new(1, m)
  cos = vec.dot(mirror) / vec.abs / mirror.abs
  cos *= -1 if next_base.y > 0
  puts "cos=#{cos}"
  vec.rotate!(cos)
  vec.rotate!(cos)
  base = next_base
  puts "#{vec} #{next_base}"
  ans += 1
end
puts ans
