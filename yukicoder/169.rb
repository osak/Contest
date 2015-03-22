#Name: 何分かかるの！？
#Level: 1
#Category: やるだけ
#Note:

# 残り時間は全体の(100-k)%に相当するので、割り算すればよい。
# ただし、誤差に注意しないとずれる。

k = gets.to_f
s = gets.to_f

puts "#{(s*100 / (100-k)).to_i}"
