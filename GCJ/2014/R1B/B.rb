#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

$memo = {}
def calc(bit, limited_a, limited_b, limited_k, a, b, k)
  if bit == -1
    return 1
  end
  key = [bit, limited_a, limited_b, limited_k].freeze
  return $memo[key] if $memo[key]
  res = 0
  a_can_be_1 = !limited_a || a[bit] == 1
  b_can_be_1 = !limited_b || b[bit] == 1
  k_can_be_1 = !limited_k || k[bit] == 1
  # (0, 0)
  res += calc(bit-1, limited_a && a[bit] == 0, limited_b && b[bit] == 0, limited_k && k[bit] == 0, a, b, k)
  # (0, 1)
  if b_can_be_1
    res += calc(bit-1, limited_a && a[bit] == 0, limited_b, limited_k && k[bit] == 0, a, b, k)
  end
  # (1, 0)
  if a_can_be_1
    res += calc(bit-1, limited_a, limited_b && b[bit] == 0, limited_k && k[bit] == 0, a, b, k)
  end
  if k_can_be_1
    # (1, 1)
    if a_can_be_1 && b_can_be_1
      res += calc(bit-1, limited_a, limited_b, limited_k, a, b, k)
    end
  end
  $memo[key] = res
end

solve do
  a, b, k = gets.split.map(&:to_i)
  a -= 1
  b -= 1
  k -= 1
  $memo = {}
  calc(31, true, true, true, a, b, k)
end
