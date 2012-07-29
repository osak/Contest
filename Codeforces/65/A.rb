#!/usr/bin/ruby

gets
ARGF.read.each_line { |line|
    line.chomp!
    line = line[0] + (line.size-2).to_s + line[-1] if line.size > 10
    puts line
}
