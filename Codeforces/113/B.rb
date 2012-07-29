#!/usr/bin/ruby

class Vector
  attr_accessor :x, :y
  def initialize(x, y)
    @x = x
    @y = y
  end

  def -(other)
    Vector.new(@x-other.x, @y-other.y)
  end

  def cross(other)
    @x*other.y - @y*other.x
  end

  def dot(other)
    @x*other.x + @y*other.y
  end

  def norm
    @x**2 + @y**2
  end

  def to_s
    "(#{@x},#{@y})"
  end
end

def ccw(p1, p2, p3)
  (p2-p1).cross(p3-p1)
end

class Convex
  def initialize(arr)
    rightmost = 0
    arr.each_with_index do |pt, idx|
      if pt.x > arr[rightmost].x
        rightmost = idx
      end
    end
    size = arr.size
    @vertices = arr[rightmost...size] + arr[0...rightmost]
  end

  def include?(point)
    # assume vector (arr[0], point)
    left = 1
    right = @vertices.size
    while left < right
      center = (left+right) / 2
      pt = @vertices[center]
      ccw = ccw(@vertices[0], pt, point)
      puts "#{@vertices[0]} #{pt} #{point}"
      ccw = 0 if ccw.abs < 1e-9
      if ccw > 0
        left = center+1
      elsif ccw < 0
        right = center
      else
        v1 = point-@vertices[0]
        v2 = @vertices[center]-@vertices[0]
        return v1.dot(v2) > 0 && v1.norm < v2.norm
      end
    end
    return false if left == @vertices.size
    ccw(@vertices[left-1], @vertices[left], point) > 0
  end
end

n = gets.to_i
a_arr = []
n.times do
  a_arr << Vector.new(*gets.split.map(&:to_f))
end
a = Convex.new(a_arr.reverse)

m = gets.to_i
ok = true
m.times do
  v = Vector.new(*gets.split.map(&:to_f))
  if not a.include?(v)
    ok = false
    break
  end
end

puts (ok ? "YES" : "NO")
