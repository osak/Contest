#!/usr/bin/env ruby

# 分母dと互いに素な数の個数は、オイラーのtotient関数で簡単に求められる。
#   φ(d) = dπ(1-(1/p_k))
# ここで、p_kはdの素因数である。
# totient関数は素因数の種類数だけに依存するから、素因数の種類を増やさずに個数だけ増やしても
# resilience φ(d) / (d-1)は増加するだけである。
# したがって、まず自明な上界として分母が素数階乗の場合が考えられ、実際に計算すると
# d = 29# = 6469693230(64.7億)を得る。
# 次に、totient関数は素因数が大きくなるにつれて減少速度が急速に低下することから、
# 真の解は2～29までの素数の組み合わせで得られると考えられる。
# したがって、素因数の組み合わせを全て試し、その制約下で先の上限値を超えないような数を全探索すればよい。

require 'rational'
require 'prime'

TARGET = 15499/94744.to_r
LIM = 6469693230 
PRIME_TAKE = 10

#Prime.each do |pr| #=> 6469693230 

ans = nil
use_prime = Prime.each.take(PRIME_TAKE)
(1..PRIME_TAKE).each do |cnt|
  use_prime.combination(cnt) do |comb|
    primes = comb
    tot = primes.map{|pr| 1 - 1/pr.to_r}.inject(&:*)
    cand = [primes.inject(&:*)]
    seen = {}
    while not cand.empty?
      n = cand.shift
      r = n * tot / (n-1)
      if r <= TARGET
        if ans.nil? or n < ans
          puts n
          puts primes.join(' ')
          ans = n
        end
      end
      primes.reverse_each do |i|
        nc = n * i
        cand << nc if nc < LIM and not seen[nc]
        seen[nc] = true
      end
    end
  end
end
puts ans

