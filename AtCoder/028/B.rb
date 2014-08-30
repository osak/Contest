# Name: 特別賞
# Level: 3
# Category: スライド最小値,BIT
# Note:

# 先頭から順に番号を見ていき、別に確保した配列上で同じ番号のところに1を足す。
# このとき、K番目に小さい数は、この配列上での累積和がちょうどKになるインデックスである。
# 累積和を高速に処理できればよいので、BITを使えばよい。
# 累積和がちょうどKになる場所は、普通に二分探索してもよいが、単調減少していくことに注目すると
# 最後に選ばれた場所より前だけを気にすればよいので高速化できる。
#
# オーダーは O(N log N)。
class BIT
  def initialize(n)
    @buf = Array.new(n, 0)
  end

  def add(i, v)
    while i < @buf.size
      @buf[i] += v
      i += i & -i
    end
  end

  def read(i)
    sum = 0
    while i > 0
      sum += @buf[i]
      i -= i & -i
    end
    sum
  end
end

n, k = gets.split.map(&:to_i)
xs = gets.split.map(&:to_i)
rev_dict = {}
xs.each_with_index do |v, i|
  rev_dict[v] = i+1
end

cur = n
bit = BIT.new(n+1)
xs.each_with_index do |x, i|
  bit.add(x, 1)
  while bit.read(cur) >= k
    cur -= 1
  end
  if i+1 >= k
    puts rev_dict[cur+1]
  end
end
