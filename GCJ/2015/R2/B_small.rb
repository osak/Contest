#!/usr/bin/env ruby

require 'mathn'

Source = Struct.new(:rate, :temp)

def solve
  n, v, x = gets.split
  n = n.to_i
  v = v.to_r
  x = x.to_r

  srcs = n.times.map{Source.new(*gets.split.map(&:to_r))}.freeze
  if n == 1
    src = srcs.first
    if src.temp != x
      return "IMPOSSIBLE"
    else
      return "%.10f" % (v / src.rate).to_f
    end
  else
    den = (srcs[1].rate*srcs[0].temp*srcs[0].rate - srcs[1].temp*srcs[1].rate*srcs[0].rate)
    if den == 0
      # Both have same temperture
      if srcs.first.temp != x
        return "IMPOSSIBLE"
      else
        return "%.10f" % (v / srcs.map(&:rate).inject(&:+)).to_f
      end
    end
    t1 = (v*x*srcs[1].rate - srcs[1].temp*srcs[1].rate*v) / den
    t2 = (v - srcs[0].rate * t1) / srcs[1].rate
    if t1 < 0 || t2 < 0
      return "IMPOSSIBLE"
    else
      return "%.10f" % [t1, t2].max.to_f
    end
  end
  raise
end

t = gets.to_i
t.times do |c|
  puts "Case ##{c+1}: #{solve}"
end

