# Name: スワップ文字列(Med)
# Level: 3
# Category: 数学

# 任意の隣り合う2つの文字を入れ替えられれば、任意の順列が構成できる。
# あとは重複順列を計算すればよい。

def fac(n)
    (1..n).reduce(&:*)
end

s = gets.chomp
cnt = s.chars.reduce({}){|h,c| h[c] ||= 0; h[c] += 1; h}.freeze
dups = cnt.values.reduce(1){|a,c| a * fac(c)}
patterns = fac(s.length) / dups
puts (patterns-1) % 573
