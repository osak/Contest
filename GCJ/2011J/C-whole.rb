#!/usr/bin/env ruby

(1..1000).each do |i|
    best = 0
    besta = 0
    (0..(i/2)).each do |a|
        b = i - a
        bits = a.to_s(2).count('1') + b.to_s(2).count('1')
        if bits > best
            best = bits
            besta = a
        end
    end

    puts "#{i}: #{best} ( #{besta} + #{i-besta} )"
end

