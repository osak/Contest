# 計算式は逆ポーランド記法によって全列挙できる。
# 全てのdigitsの組み合わせに対し、すべての計算式を試す。
require 'rational'
require 'set'

def permutate(syms, stk, buf)
  if stk.size == 7
    buf << stk.dup
  else
    allow_ops = 3 - syms.size
    op_cnt = stk.size - (4-syms.size)
    if op_cnt < allow_ops
      [:+, :-, :*, :/].each do |op|
        permutate(syms, stk+[op], buf)
      end
    end
    syms.each do |sym|
      permutate(syms-[sym], stk+[sym], buf)
    end
  end
  buf
end

EXPRS = permutate((0..3).to_a, [], []).freeze
puts EXPRS.size

def evaluate(expr, digits)
  stk = []
  begin
    expr.each do |sym|
      if sym.is_a?(Integer)
        stk << digits[sym]
      else
        a = stk.pop
        b = stk.pop
        stk << a.__send__(sym, b)
      end
    end
    stk[0]
  rescue
    nil
  end
end

maxlen = 0
(0..9).to_a.map(&:to_r).combination(4) do |comb|
  res = Set.new(EXPRS.map{|expr| evaluate(expr, comb)})
  len = 0.to_r
  loop do
    break unless res.include?(len+1)
    len += 1
  end
  if len > maxlen
    puts comb.join(' ')
    maxlen = len
  end
end
