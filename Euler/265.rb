# 今までに見つかった数と直前N-1桁のパターンを覚えながらDFS。

require 'memoize'

N = 5
LIM = 2**N
MASK = (1<<N)-1

def calc(pos, found, prev, sum)
  #puts "#{pos} #{found} #{prev} #{sum}"
  if pos == LIM
    (N-1).times do
      prev <<= 1
      prev &= MASK
      return 0 if found[prev] == 1
      found |= (1<<prev)
    end
    return sum
  end
  res = 0
  # for zero
  next_pat = (prev<<1) & MASK
  if found[next_pat].zero?
    res += calc(pos+1, found | (1<<next_pat), next_pat, sum)
  end
  #for one
  next_pat = ((prev<<1) & MASK) + 1
  if found[next_pat].zero?
    res += calc(pos+1, found | (1<<next_pat), next_pat, sum+(1<<(LIM-pos-1)))
  end
  res
end

puts calc(N, 1, 0, 0)
