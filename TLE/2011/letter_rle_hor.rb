#!/usr/bin/ruby

arr = []
('A'..'Z').each { |c|
    src = File.readlines("LETTER_CHARS/#{c}")
    str = ''
    flg = 0
    prev = src[0]
    cnt = 1
	b = 0
    13.times { |i|
        8.times { |j|
            if src[j][i] != prev
                b <<= 4
                b += cnt
                flg += 1
                if flg == 2
                    str += b.chr
                    flg = 0
                    b = 0
                end
                prev = src[j][i]
                cnt = 1
            else
                cnt += 1
            end
        }
    }
    arr << str
}
puts arr.join('')
