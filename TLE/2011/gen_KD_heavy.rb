#!/usr/bin/ruby

p 10
10.times {
    puts "1 4 10000"
    5000.times { |i|
        puts "0 1 1"
    }
    5000.times { |i|
        puts "1 1 100"
    }
}
