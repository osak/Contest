#!/usr/bin/env ruby

gets.to_i.times do |cases|
    m, c, w = gets.split.map(&:to_i)
    cards = (1..m).to_a
    c.times do
        a, b = gets.split.map(&:to_i)
        a -= 1
        cards = cards[a,b] + cards[0...a] + cards[(a+b)...m]
    end
    puts "Case ##{cases+1}: #{cards[w-1]}"
end
