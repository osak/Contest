#!/usr/bin/env ruby

# ある数n以下のbouncy numberは、
#   [何桁目][直前の数][上限有無][increasing][decreasing]
# を状態としたDPによって計算できる。

class Calc
  def initialize(limit)
    @limit = limit.to_s.each_char.map(&:to_i).freeze
    @memo = {}
  end

  def calc
    calc_inner(0, nil, true, true, true)
  end

  def calc_inner(pos, prev, limited, inc, dec)
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
      res += calc_inner(pos+1, ndig, nlim, ninc, ndec)
    end
    #puts "#{pos} #{prev} #{limited} #{inc} #{dec} #{res}"
    #puts @step
    @memo[tag] = res
  end
end

GOOGOL = 10**100
calc = Calc.new(GOOGOL)
bouncy = calc.calc
puts GOOGOL - bouncy - 1
