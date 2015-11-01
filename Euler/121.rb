#!/usr/bin/env ruby

require 'rational'

prob = 1.to_r
15.times do |i|
  prob *= 1/(i+2).to_r
end
prob *= 2**14
puts prob
