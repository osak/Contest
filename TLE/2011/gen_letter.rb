#!/usr/bin/ruby

arr = []
('A'..'Z').each { |c|
    lines = File.readlines("LETTER_CHARS/#{c}")
    str = ''
    13.times { |i|
        b = 0
        8.times { |j|
            b <<= 1
            b += 1 if lines[j][i] == '1'
        }
        str += b.chr
    }
    arr << str
}
puts arr.join('')
