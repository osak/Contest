# 二等辺三角形で、長さの違う辺を底辺に考えると
# 長さの同じ辺を斜辺としたピタゴラス数のうち、
# 条件を満たすものを列挙する問題になる。
LIMIT = 1_000_000_000
ans = 0
catch(:finish) {
  (1..Float::INFINITY).each do |n|
    start = n.odd? ? 2 : 1
    (start...n).step(2) do |m|
      next if n.gcd(m) != 1
      base_a = n*n - m*m
      base_b = 2*n*m
      base_c = n*n + m*m
      #puts "#{base_a} #{base_b} #{base_c}"
      base_a, base_b = base_b, base_a if base_a > base_b
      base_len = base_a + base_b + base_c
      a, b, c = base_a, base_b, base_c
      len = base_len
      throw :finish if len > LIMIT
      while len < LIMIT
        break if c > a*2+1
        if c == a*2+1 || c == a*2-1
          ans += c+c+a*2
          puts "#{a*2} #{c} (#{ans})"
          break
        end
        a, b, c = a+base_a, b+base_b, c+base_c
        len += base_len
      end
    end
  end
}
puts ans
