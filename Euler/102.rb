#!/usr/bin/env ruby

# 原点から各頂点に向けたベクトルを一定の向きにたどり、外積の符号がずっと同じなら原点は内部にある。

class Numeric
  def sign
    self == 0 ? 0 : self < 0 ? -1 : 1
  end
end

def cross(x1, y1, x2, y2)
  x1*y2 - x2*y1
end

cnt = 0
File.open("triangles.txt").each_line do |line|
  x1, y1, x2, y2, x3, y3 = line.split(/,/).map(&:to_i)
  c1 = cross(x1, y1, x2, y2).sign
  c2 = cross(x2, y2, x3, y3).sign
  c3 = cross(x3, y3, x1, y1).sign
  cnt += 1 if [c1, c2, c3].all?{|c| c == c1}
end
puts cnt
