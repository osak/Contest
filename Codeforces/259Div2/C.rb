# Name: Little Pony and Crystal Mine
# Level: 3
# Category: 数学,Math,確率,Probability

# Consider the probability of "at most i is appeared among all rolls."
# It can be calculated as:
#   (i/m)^n
# since only 1 to i are allowed to appear.
# The probability of "i is the maximum number among all rolls" is derived from this;
# "at most i is appeared among all rolls" and not "at most (i-1) is appeared among all rolls."
# Hence, the demanded probability can be caluculated as:
#   (i/m)^n - ((i-1)/m)^n

m, n = gets.split.map(&:to_i)
ans = 0.0
(1..m).each do |k|
  ans += k * (((k.to_f/m) ** n) - ((k-1.to_f) / m) ** n)
end

printf "%.8f\n", ans
