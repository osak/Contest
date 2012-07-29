#!/usr/bin/ruby

h, m = gets.split(':').map(&:to_i)
3600.times do |i|
    m += 1
    if m == 60
        m = 0
        h += 1
        if h == 24
            h = 0
        end
    end

    hstr = sprintf("%02d", h)
    mstr = sprintf("%02d", m)

    if mstr.reverse == hstr
        puts "#{hstr}:#{mstr}"
        exit
    end
end
