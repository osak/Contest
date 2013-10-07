#!/usr/bin/env ruby

# logを取って比較する。

anslog = 0
File.open("base_exp.txt").each_line.with_index do |line, idx|
  base, exp = line.split(/,/).map(&:to_i)
  log = exp * Math.log(base)
  if log > anslog
    puts "#{idx+1}: #{line.chomp}"
    anslog = log
  end
end

