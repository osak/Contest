#Name: 金塊ゲーム
#Level: 3
#Category: 動的計画法,DP
#Note:

# 最初に動かすクレーンを決めると、盤面が4分割される。
# 分割されたそれぞれのエリアはすべて金塊で埋まっており、
# かつ他のエリアに干渉することはできないので、最初の状態と同じ議論ができる。
# 考えるべき領域の端点になり得る座標は、x座標、y座標ともに各クレーンの座標か、端の座標かのどちらかである。
# したがって、計算すべき状態数はO(N^2)個である。
#
# オーダーは O(N^3)。
# DPは入力が大きいことが多いが、この問題は入力が小さいのでRubyでも通る。神。
require 'ostruct'
w, h = gets.split.map(&:to_i)
n = gets.to_i
machines = n.times.map{
  a = gets.split.map(&:to_i)
  OpenStruct.new(x: a[0], y: a[1])
}

$memo = {}
def calc(x, y, ex, ey, ms)
  key = [x, y, ex, ey].freeze
  if $memo.has_key?(key)
    return $memo[key]
  end

  inner_machines = ms.select{|m| (x..ex).include?(m.x) && (y..ey).include?(m.y)}
  res = 0
  inner_machines.each do |m|
    l = m.x - x
    r = ex - m.x
    u = m.y - y
    d = ey - m.y
    tmp = l + r + u + d + 1 + 
      calc(x, y, m.x-1, m.y-1, ms) +
      calc(m.x+1, y, ex, m.y-1, ms) +
      calc(m.x+1, m.y+1, ex, ey, ms) +
      calc(x, m.y+1, m.x-1, ey, ms)
    if res < tmp
      res = tmp
    end
  end
  $memo[key] = res
  res
end

$memo = {}
puts calc(1, 1, w, h, machines)
