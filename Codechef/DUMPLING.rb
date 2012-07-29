#!/usr/bin/ruby

gets.to_i.times do
  a,b,c,d,k = gets.split.map(&:to_i)

  pstep = a.gcd(b)
  sstep = c.gcd(d)
  step = pstep.lcm(sstep)

  p (k/step)*2+1
end
