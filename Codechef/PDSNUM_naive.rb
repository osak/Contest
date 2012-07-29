#!/usr/bin/ruby

loop do
  n = gets.to_i
  break if n == 0

  i = 1
  pdscnt = 0
  loop do
    prod = 1
    sum = 0
    tmp = i
    while tmp > 0
      d = tmp % 10
      if d == 0
        prod = 0
        sum = 1
        break
      end
      prod *= d
      sum += d
      tmp /= 10
    end
    if prod % sum == 0
      pdscnt += 1
      puts "#{pdscnt}: #{i}"
      puts "#{pdscnt}: #{i}" if pdscnt == n
      break if pdscnt == n
    end
    i += 1
  end
end

