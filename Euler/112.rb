#!/usr/bin/env ruby

# ある数n以下のbouncy numberは、
#   [何桁目][直前の数][上限有無][increasing][decreasing]
# を状態としたDPによって計算できる。

class Calc
  def initialize(limit)
    @limit = limit.to_s.each_char.map(&:to_i).freeze
    @memo = {}
  end

  def calc(pos=0, prev=nil, limited=true, inc=true, dec=true)
    tag = [pos, prev, limited, inc, dec]
    return @memo[tag] if @memo[tag]

    if pos == @limit.size
      if (not inc) and (not dec)
        return 1
      else
        return 0
      end
    end

    lim = limited ? @limit[pos] : 9
    res = 0
    (0..lim).each do |digit|
      nlim = limited && (digit == lim)
      ninc = inc && (digit >= (prev||0))
      ndec = dec && (digit <= (prev||9))
      ndig = (prev.nil? && digit == 0) ? nil : digit
      res += calc(pos+1, ndig, nlim, ninc, ndec)
    end
    #puts "#{pos} #{prev} #{limited} #{inc} #{dec} #{res}"
    @memo[tag] = res
  end
end

left, right = 0, 10000000
while left+1 < right
  n = (left + right) / 2
  cnt = Calc.new(n).calc
  ratio = cnt.to_f / n
  if ratio < 0.99
    left = n + 1
  else
    right = n
  end
end
puts left
