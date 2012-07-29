#!/usr/bin/ruby

puts ARGV[0]
ARGV[0].to_i.times { |n|
    a = []
    256.times { |i|
        a << (rand() * 1000).to_i
    }
    a << -1
    puts a.join(' ')
    STDERR.puts n
}

