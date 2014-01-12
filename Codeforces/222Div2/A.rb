# Name: Dice
# Level: 1
# Category: やるだけ
# Note:

# 全探索するだけ。

a, b = gets.split.map(&:to_i)
awin, draw, bwin = 0, 0, 0
(1..6).each do |i|
  da = (i-a).abs
  db = (i-b).abs
  if da < db
    awin += 1
  elsif da > db
    bwin += 1
  else
    draw += 1
  end
end
puts "#{awin} #{draw} #{bwin}"
