#!/usr/bin/env ruby

$<.each_line do |line|
  print line.to_i(2).chr
end
