# D'(n, k) = F(n)のk文字目とすると、F(n) = F(n-2)F(n-1)より、
# D'(k) = 
#   ・k <  |F(n-2)| のとき、F(n-2)[k]
#   ・k >= |F(n-2)| のとき、F(n-1)[k-F(n-2)]
A = "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679".freeze
B = "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196".freeze
LIMIT = (127+19*17)*(7**17)

digits = [100, 100]
while digits[-1] < LIMIT
  digits << digits[-1]+digits[-2]
end
puts digits.size

ans = ""
(0..17).reverse_each do |x|
  k = (127+19*x) * (7**x) - 1
  n = digits.index{|a| a >= k}
  while n > 1
    if k < digits[n-2]
      n = n-2
    else
      k = k-digits[n-2]
      n = n-1
    end
  end
  ans << [A, B][n][k]
end
puts ans
