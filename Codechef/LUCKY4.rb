#!/usr/bin/ruby

class Numeric
  def lucky?
    self == 4 || self == 7
  end
end

$maxn = 0
$limit = []
$c = []
$memo = {}

# n番目の数のm桁目以降を自由に決めるときのパターン数．
# fはn番目の数の中でのLucky Number数．
# prevはn-1番目のLucky Number数．
# limitedがtrueのときは，全体でMを越えないようにするためm桁目の数字に上限を設ける．
def solve(n, m, f, prev, limited)
  #puts "#{n} #{m} #{f} #{prev} #{limited}"

  # Base case
  if n == $maxn
    return 1 
  end

  # n番目の数字が決まったら正当性チェックする．
  if m == -1
    return 0 if n > 0 && (f == prev) != $c[n-1]
    return solve(n+1, $limit.size-1, nil, f, true)
  end

  key = [n,m,f,prev,limited]
  res = $memo.fetch(key, nil)
  return res if res

  # 使える数字の上限と下限．
  # A[n] >= 1でないといけないことに注意．
  lim = limited ? $limit[m] : 9
  bot = (m == 0 && f.nil?) ? 1 : 0
  #puts "#{n} #{m} #{f} #{prev} #{limited}: lim=#{lim}"
  
  res = 0
  (bot..lim).each do |d|
    nf = d.lucky? ? f.to_i+1 : (f.nil? && d == 0) ? nil : f.to_i
    nl = limited && (d == lim)
    res += solve(n, m-1, nf, prev, nl)
    # 高速化のための枝刈り．
    # Mは高々10^9なので，それを越えるパターン数を求めても仕方がない．
    # （単純に再帰が増えるだけではなく，Bignumになってしまうと激遅になる）
    break if res > 2000000000
  end
  #puts "#{n} #{m} #{f} #{prev} #{limited}: #{res}"
  $memo[key] = res
end

gets.to_i.times do
  $maxn, m, k = gets.split.map(&:to_i)
  $c = gets.split.map{|c| c == "1"}
  $limit = m.to_s.each_char.to_a.map(&:to_i).reverse
  $memo.clear

  ans = []
  prevf = 0
  acc = 0
  catch(:end) do
    $maxn.times do |pos|
      num = 0
      limited = true
      f = nil
      # 上の桁から固定していき，それ以降のパターン数を数える．
      (0..$limit.size-1).to_a.reverse_each do |dpos|
        lim = limited ? $limit[dpos] : 9
        bot = (dpos == 0 && f.nil?) ? 1 : 0
        digit = nil
        (bot..lim).each do |d|
          nf = d.lucky? ? f.to_i+1 : (f.nil? && d == 0) ? nil : f.to_i
          nl = limited && (d==lim)
          tmp = solve(pos, dpos-1, nf, prevf, nl)
          #puts "#{d}: #{acc+tmp}"
          if acc + tmp >= k
            digit = d
            f = nf
            break
          end
          acc += tmp
        end
        if digit.nil?
          ans = [-1]
          throw :end
        end

        num *= 10
        num += digit
        limited = limited && (digit == lim)
      end
      ans << num
      prevf = f
    end
  end

  puts ans.join(" ")
end
