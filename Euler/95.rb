# n = p1^k1 p2^k2 …… pn^kn として、約数の和は
# Π(1+p1+p1^2+……p1^k)(1+p2+……)……(1+pn+……)
# と書ける。
# ループ検出しながら、すべての開始点を試す（ただし後半は試してない）
require 'prime'
require 'set'
require 'memoize'
include Memoize

def divisors_sum_of(n)
  return 0 if n == 0
  return 1 if n == 1
  divs = n.prime_division
  divs.map{|pr,n| (0..n).to_a.reduce(0){|acc,k| acc+pr**k}}.inject(&:*) - n
end
memoize :divisors_sum_of

LIMIT = 1_000_000
seen = Set.new
ans = 0
(1..LIMIT).each do |n|
  next if seen.include?(n)
  puts n if n % 10000 == 0
  cur = n
  history = [cur]
  memo = {}
  step = 0
  loop do
    cur = divisors_sum_of(cur)
    break if cur > LIMIT
    if memo[cur]
      loop_len = step - memo[cur]
      loop_arr = history[-loop_len..-1]
      if loop_len > ans
        ans = loop_len
        puts "#{ans} #{loop_arr.min}"
      end
      break
    end
    memo[cur] = step
    history << cur
    step += 1
  end
  history.each do |h|
    seen << h
  end
end
