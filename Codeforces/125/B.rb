#!/usr/bin/env ruby

def pow(n)
  n*n
end

class Circle
  attr_accessor :x, :y, :r
  def initialize(x, y, r)
    @x = x
    @y = y
    @r = r
  end

  def include?(other)
    @r >= other.r && pow(@x-other.x) + pow(@y-other.y) <= pow(@r-other.r)
  end

  def collide?(other)
    (not include?(other)) && (not other.include?(self)) && pow(@x-other.x) + pow(@y-other.y) < pow(@r+other.r)
  end

  def in(area)
    area[1].include?(self) and not area[0].include?(self)
  end
end

black_area = []
circles = []
2.times do
  x, y, r1, r2 = gets.split.map(&:to_i)
  c1 = Circle.new(x, y, r1)
  c2 = Circle.new(x, y, r2)
  circles.push(c1, c2)
  black_area << [c1, c2]
end

cnt = 0
circles.each_with_index do |c1, i|
  valid = circles.all?{|c2| c1==c2 or not c1.collide?(c2)}
  valid = valid && !c1.in(black_area[1-i/2])
  cnt += 1 if valid
end

p cnt
