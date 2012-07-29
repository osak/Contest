#!/usr/bin/env ruby

str = "1"
cnt = ARGV[0].to_i
while cnt > 0
    cnt -= str.size
    str.succ!
end
puts str
