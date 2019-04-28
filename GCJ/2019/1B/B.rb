t, w = gets.chomp.split.map(&:to_i)
(1..t).each do |cn|
  rings = [0] * 7

  puts 56
  STDOUT.flush
  day56 = gets.to_i
  rings[1] = (day56 >> 56) & 0x7f
  rings[2] = (day56 >> 28) & 0x7f

  puts 168
  STDOUT.flush
  day168 = gets.to_i
  rings[3] = (day168 >> 56) & 0x7f
  rings[4] = (day168 >> 42) & 0x7f

  x = day56 - (rings[1]*(2**56) + rings[2]*(2**28) + rings[3]*(2**18) + rings[4]*(2**14))
  y = day168 - (rings[3]*(2**56) + rings[4]*(2**42))
  STDERR.puts "#{x} #{y}"
  STDERR.puts "#{(y - x*(2**19)) % ((2**33) - (2**30))}"
  rings[5] = (y - x*(2**19)) / ((2**33) - (2**30))
  rings[6] = ((x - rings[5]*(2**11)) >> 9) & 0x7f

  ans = rings[1..6].join(' ')
  puts ans
  STDOUT.flush
  result = gets.to_i
  STDERR.puts "Case ##{cn}: #{ans} #{result}"
end
