#!/usr/bin/ruby

File.open('2190.big.in', 'w') do |f|
    arr = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B']
    stair = []
    music = []
    50000.times {
        idx = rand(0)
        stair << arr[idx]
    }
    stair << 'B'
    50000.times {
        idx = rand(0)
        music << arr[idx]
    }
    f.puts('1')
    f.puts('50001 50000')
    f.puts(stair.join(' '))
    f.puts(music.join(' '))
end
