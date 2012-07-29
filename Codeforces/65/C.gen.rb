N = 10**5
p N
puts Array.new(N).map{(rand()*10%2).to_i}.join(' ')
