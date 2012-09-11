#!/usr/bin/ruby

class Numeric
  def should(val)
    if self != val
      caller.first =~ /^(.+?):(\d+)/
      STDERR.puts "test failed: #{$1}:#{$2} expected #{val} but got #{self}"
    end
  end

  def lucky_digit?
    self == 4 || self == 7
  end
end

def lcnt(n, i)
  if n == 0
    return 1
  end
  if n == 1
    return 2 if i == 1
    return 7 if i == 0
    return 0
  end

  a = i > 0 ? 2*(([0,i-1].max..n-1).reduce(0){|acc, val| acc+lcnt(val,i-1)}) : 0
  b = n > i ? 7*(([0,i].max..n-1).reduce(0){|acc, val| acc+lcnt(val,i)}) : 0
  a + b
end

def lcnt2(n, i, lims, limited)
  return 1 if n == 0

  usable = (1..9).to_a.select{|i| limited ? i <= lims[0] : true}
  if n == 1
    return usable.count{|i| i.lucky_digit?} if i == 1
    return usable.count{|i| !i.lucky_digit?} if i == 0
    return 0
  end
  a = b = 0
  if limited
    usable.each do |digit|
      flag = limited && digit == lims[0]
      if digit.lucky_digit?
        a += i > 0 ? ([0,i-1].max..n-1).reduce(0){|acc,val| acc+lcnt2(val,i-1,lims[n-val..-1],flag)} : 0
      else
        b += n > i ? ([0,i].max..n-1).reduce(0){|acc,val| acc+lcnt2(val,i,lims[n-val..-1],flag)} : 0
      end
    end
  else
    a = i > 0 ? 2*(([0,i-1].max..n-1).reduce(0){|acc,val| acc+lcnt2(val,i-1,lims[n-val..-1],false)}) : 0
    b = n > i ? 7*(([0,i].max..n-1).reduce(0){|acc,val| acc+lcnt2(val,i,lims[n-val..-1],false)}) : 0
  end
  a+b
end

def solve(n, m, rem, prev, pat, acc)
  

def unittest
  lcnt(2, 0).should(56)
  lcnt(2, 1).should(30)
  lcnt(2, 2).should(4)

  lim = 99.to_s.split(//).map(&:to_i)
  lcnt2(2, 0, lim, true).should(56)
  lcnt2(2, 1, lim, true).should(30)
  lcnt2(2, 2, lim, true).should(4)

  lim = 30.to_s.split(//).map(&:to_i)
  lcnt2(2, 0, lim, true).should(17)
  lcnt2(2, 1, lim, true).should(4)
  lcnt2(2, 2, lim, true).should(0)

  lim = 499.to_s.split(//).map(&:to_i)
  lcnt2(3, 0, lim, true).should(192)
  lcnt2(3, 1, lim, true).should(160)
  lcnt2(3, 2, lim, true).should(44)
  lcnt2(3, 3, lim, true).should(4)

  lim = 999999999.to_s.split(//).map(&:to_i)
  sum = 0
  (0..8).each do |i|
    tmp = lcnt2(8, i, lim, true)
    sum += tmp
    p tmp
  end
  sum.should(90000000)
end

unittest
