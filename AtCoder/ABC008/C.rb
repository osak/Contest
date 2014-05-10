#Name: コイン
#Level: 3
#Category: 数学,Math確率,Probability
#Note:

# それぞれのコインについて、表になる確率は独立に考えてよい。
# あるコインが表になるのは、そのコインより左にある約数のコインが偶数枚のとき。
# 他のコインは考えなくてよいので、そのようなパターンを列挙する。
#
# オーダーは O(N^2 log C)。
# コンビネーションの計算などは前計算しておけばもっと速くできそう。
def perm(n)
  return 1 if n == 0
  (1..n).reduce(&:*)
end

def comb(n, k)
  return 1 if k == 0
  ((n-k+1)..n).reduce(&:*) / (1..k).reduce(&:*)
end

n = gets.to_i
cs = n.times.map{gets.to_i}

ans = 0.0
cs.each_with_index do |c, i|
  divs = cs.each_with_index.count{|d,j| c % d == 0 && i != j}
  pat = perm(divs+1).to_f
  (0..divs).step(2) do |k|
    ans += comb(divs, k) * perm(k) * perm(divs-k) / pat
  end
end

puts "%.8f" % [ans]
