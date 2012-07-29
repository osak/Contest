#!/usr/bin/ruby

cases = gets.to_i
1.upto(cases) { |num|
    n, *arr = gets.chomp.split
    seq = []
    n.to_i.times do |i|
        seq << [arr[i*2], arr[i*2+1].to_i]
    end

    ans = 0
    state = {'O' => [1,0], 'B' => [1,0]}
    seq.each do |btn|
        s = state[btn[0]]
        min = s[1] + (s[0]-btn[1]).abs + 1
        if min > ans
            ans = min
        else
            ans += 1
        end
        state[btn[0]] = [btn[1], ans]
    end
    puts "Case ##{num}: #{ans}"
}
