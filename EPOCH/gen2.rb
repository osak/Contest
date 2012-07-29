#!/usr/bin/ruby

ARGV[0].to_i.times { |i|
    puts (rand()*10000).to_i
}
puts -1
