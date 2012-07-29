H = 1000
W = 1000
L = 100000

puts [H, W, L].join(' ')
puts 'L'*L
H.times do
    puts '.'*W
end
puts '0 0 0'
