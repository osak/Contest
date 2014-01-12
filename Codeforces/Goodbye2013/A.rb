# Name: New Year Candles
# Level: 1
# Category: シミュレーション,やるだけ
# Note:

# 燃えかすの本数を持ってシミュレーション。

a, b = gets.split.map(&:to_i)
burned = 0
ans = 0
while a > 0
  ans += a
  burned += a
  a = burned / b
  burned -= a*b
end
puts ans
