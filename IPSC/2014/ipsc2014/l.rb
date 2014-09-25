#!/usr/bin/env ruby

1600.times do |i|
  puts "sox l1.wav l1/%04d.wav trim %f %f" % [i, i*0.55, 0.55]
end
