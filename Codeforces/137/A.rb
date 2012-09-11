#!/usr/bin/env ruby

#Name: Shooshuns and Sequence
#Level: 2
#Category: シミュレーション
#Note: Codeforces #137

# k個目より後ろが初期状態で全て同じでないと，全体が揃う前にその数字が後ろにコピーされてしまうので
# 揃えることができなくなる．
# この条件を満たしているとき，k-1手かけて先頭k-1個を削除すれば全体が揃うが，実際には
# k個目から逆順に同じ数字が並んでいる場合にはもっと早く終わることに注意．
# 4 3
# 3 1 1 1
# など．

n, k = gets.split.map(&:to_i)
as = gets.split.map(&:to_i)
subseq = as[k-1...as.size]
if subseq.any?{|v| v != subseq.first}
  puts -1
  exit
end
pos = k-2
turn = k-1
while pos >= 0 && as[pos] == subseq.first
  pos -= 1
  turn -= 1
end
puts turn
