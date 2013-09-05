#!/usr/bin/env ruby

# P, Qとして全ての点を試す。

LIM = 50

ans = 0
# P(x1, y1), Q(x2, y2)
(0..LIM).each do |x1|
  (0..LIM).each do |y1|
    p1 = [x1, y1]
    next if p1 == [0, 0]
    (0..LIM).each do |x2|
      (0..LIM).each do |y2|
        p2 = [x2, y2]
        next if (p2 == [0, 0]) or (p1 == p2)
        if x1*x2 + y1*y2 == 0
          # right angle at origin
          ans += 1
        elsif x1*(x2-x1) + y1*(y2-y1) == 0
          # right angle at P
          ans += 1
        elsif x2*(x1-x2) + y2*(y1-y2) == 0
          # right angle at Q
          ans += 1
        end
      end
    end
  end
end
puts ans/2
