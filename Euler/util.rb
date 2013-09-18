def fastpow_mod(a, x, mod)
  res = 1
  ord = a % mod
  while x > 0
    if x.odd?
      res *= ord
      res %= mod
    end
    ord *= ord
    ord %= mod
    x /= 2
  end
  res
end

