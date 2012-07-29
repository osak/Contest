#!/usr/bin/ruby

$memo = {}
def rec2(n, rem)
  return 1 if rem == 0
  if n == 0
    return 1 if rem == 0
    return 0
  end

  key = [n,rem]
  val = $memo.fetch(key, nil)
  return val if val

  res = 0
  (0..9).each do |d|
    break if d > rem
    res += rec2(n-1, rem-d)
  end
  $memo[key] = res
end

$memo2 = Array.new(91){Hash.new}
def rec(n, rem, prod, sum)
  if n == 0
    return 1 if rem == 0 && prod % sum == 0
    return 0
  end
  return 1 if rem == 0
  return 0 if n*9 < rem

  if !prod.nil? && prod % sum == 0
    return rec2(n, rem)
  end

  key = [n, rem, prod]
  val = $memo2[sum].fetch(key, nil)
  return val if val

  res = 0
  (0..9).each do |d|
    break if d > rem
    nprod = (prod.nil? && d == 0) ? nil : (prod||1)*d
    res += rec(n-1, rem-d, nprod, sum)
  end
  $memo2[sum][key] = res
end

$memo3 = {}
def solve(n)
  ans = 0
  prod = nil
  sum = 0
  pat = 0
  (1..10).to_a.reverse.each do |nth|
    ans *= 10
    digit = nil
    (0..9).each do |d|
      nprod = (prod.nil? && d == 0) ? nil : (prod||1)*d
      key = [nth, d, sum, nprod]
      subpat = $memo3.fetch(key, nil)
      if subpat.nil?
        subpat = 0
        (1..90).each do |allsum|
          subpat += rec(nth-1, allsum-sum-d, nprod, allsum) if allsum >= sum+d
        end
        $memo3[key] = subpat
      end
      p subpat
      if pat + subpat >= n
        digit = d
        break
      end
      pat += subpat
    end

    if digit.nil?
      puts "NEVER REACH HERE!"
    end
    ans += digit
    sum += digit
    #puts "#{nth}th digit: #{digit}"
    if ans != 0
      prod ||= 1
      prod *= digit
    end
  end
  ans
end

loop do
  n = gets.to_i
  break if n == 0
  p solve(n)
end

