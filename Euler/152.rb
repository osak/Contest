#!/usr/bin/env ruby

require 'rational'

$sum = []
$sum[46] = 0
(2..45).reverse_each do |i|
  $sum[i] = $sum[i+1] + 1/(i*i).to_r
end

def dfs(den, cur, seq)
  if cur == 1/2.to_r
    puts seq.join(' ')
    return 1
  end
  return 0 if den > 45
  return 0 if cur + $sum[den] < 1/2.to_r

  val = cur + 1/(den*den).to_r
  res = 0
  if val <= 1/2.to_r
    seq << den
    res += dfs(den+1, val, seq)
    seq.pop
  end
  res += dfs(den+1, cur, seq)
  res
end

dfs(2, 0, [])
