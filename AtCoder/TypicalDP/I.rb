#!/usr/bin/env ruby

# iwiを消せるパターンとして、まず見えるのが
# ・iiwi, iwii： iwiを消してiに置換しても等価
# これを可能な限り適用すると、残ったiwiは消しても新しくiwiが生成されることはない。
# （残ったiwiの両側は常にwであり、iwiを消すとwwが生成されるため。）
# したがって、左から順にiwiを消していけば最も多くiwiを消せる。

s = gets.chomp
cnt = 0
loop do
  cur = cnt
  s.gsub!(/iiwi/){cnt += 1; "i"}
  s.gsub!(/iwii/){cnt += 1; "i"}
  break if cur == cnt
end
s.gsub!(/iwi/){cnt += 1; ""}
puts cnt
