#!/usr/bin/env ruby

# 各列ごとに、pos行目にたどりつくまでの最小コストをDPによって計算する。
# （コードでは簡単のため、行列を転置して扱っている）

matrix = $<.each_line.to_a.map{|line| line.split(/,/).map(&:to_i)}.transpose
INF = matrix.flatten.inject(&:+)

come_best = Array.new(matrix.size, 0)
matrix.each do |row|
  end_best = Array.new(row.size, INF)
  (0...row.size).each do |start|
    # End at here
    end_best[start] = [end_best[start], come_best[start] + row[start]].min
    # Go left
    (0...start).reverse_each do |pos|
      end_best[pos] = [end_best[pos], end_best[pos+1] + row[pos]].min
    end
    # Go right
    (start+1...row.size).each do |pos|
      end_best[pos] = [end_best[pos], end_best[pos-1] + row[pos]].min
    end
  end
  come_best = end_best
  #puts come_best.join(' ')
end

puts come_best.min
