#!/usr/bin/ruby

cnt = 0;
[1,2,3,4].permutation do |arr|
  flag = true
  arr.each_with_index do |v, idx|
    if v == idx+1
      flag = false
      break
    end
  end
  if flag
    puts arr.join(' ')
    cnt += 1
  end
end
puts cnt
