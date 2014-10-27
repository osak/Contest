# -*- coding: utf-8 -*-
# Name: 錬金術師
# Level: 3
# Category: 文字列,動的計画法,DP
# Note:

# 各文字列に含まれる種類ごとの文字の数さえ覚えておけば良い。
# 文字をAからZまで順番に試していき、その文字までで条件を満たしつつ、
# s1からちょうどi文字だけ取っているという取り方が可能かどうかでDPする。
#
# s1から取らなければならない文字数は、22の文字を使えるだけ使った時が最低で、
# s1の文字を使えるだけ使った時が最高。
# したがって、直前までの状態で、「i-最高文字数」から「i-最低文字数」までのどれかを実現できるのであれば、
# ちょうどi文字だけ使うというパターンも可能であることがわかる。
# （ただし、iに関して、s2からN文字より多く取るようなものは無条件で無効としなければならないことに注意）
#
# オーダーは O(CN)。
# ただしCはs3に含まれる文字の種類数。

def cnt(s)
  s.each_char.reduce(Hash.new{|h,k| h[k] = 0}){|h,c| h.tap{|hh| hh[c] ||= 0; hh[c] += 1}}
end

a1, a2, a3 = $<.each_line.map{|s| cnt(s.chomp)}
N = a1.values.inject(&:+) / 2

dp = Array.new(N+1, 1)

acc = 0
a3.each_pair do |c, v|
  ndp = Array.new(N+1, 0)
  min_use = [0, a3[c] - a2[c]].max
  max_use = [a3[c], a1[c]].min
  if a1[c] + a2[c] < a3[c]
    puts "NO"
    exit
  end
  acc += a3[c]
  ([acc-N, 0].max..N).each do |i|
    l = i - max_use
    r = i - min_use
    next if r < 0
    ndp[i] = 1 if (l <= 0 && dp[r] != 0) || (l > 0 && dp[l-1] != dp[r])
  end

  (1..N).each do |i|
    ndp[i] += ndp[i-1]
  end
  dp = ndp
  #puts dp.join(' ')
end

puts (dp[N] != 0 ? "YES" : "NO")
