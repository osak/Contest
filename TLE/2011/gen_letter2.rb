#!/usr/bin/ruby

arr = []
('A'..'Z').each { |c|
    src = File.readlines("LETTER_CHARS/#{c}").map(&:chomp).join('')
    str = ''
    b=0
    src.size.times { |i|
        b <<= 1
        b += 1 if src[i] == '1'
        if i % 8 == 7
            str += b.chr 
            b = 0
        end
    }
    arr << str
}
puts arr.join('')
