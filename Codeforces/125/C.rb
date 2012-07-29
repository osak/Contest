#!/usr/bin/env ruby

k,b,n,t = gets.split.map(&:to_i)

if k == 1
  puts [0, ((1+n*b-t)/b.to_f).ceil].max
else
  lim = Math.log(t) / Math.log(k)
  left = 0
  right = n
  30.times do
    center = (left+right) / 2
    if n-center > lim
      left = center+1
    else
      sum = k**(n-center) + b*(1-k**(n-center))/(1-k)
      if sum <= t
        right = center
      else
        left = center+1
      end
    end
  end

  puts (left+right)/2
end
