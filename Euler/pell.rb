# Solve pell equation
#   x^2 - dy^2 = 1
# and yields each solution.
def each_pelleq_solutions(d)
  Enumerator.new {|y|
    # x1/y1 is fractional representation of continued fraction,
    # up to n-th fraction.
    x1, x2, y1, y2 = 1, 0, 0, 1
    # (a + b*sqrt(d)) / c is most low-level fraction.
    a, b, c = 0, 1, 1

    loop do
      if c == 0
        break
      end
      n = ((a + (b*b*d)**0.5)/c).to_i
      x1, x2 = n*x1+x2, x1
      y1, y2 = n*y1+y2, y1
      if x1*x1 - d*y1*y1 == 1
        y << [x1, y1]
      end

      k = a - n*c
      a, b, c = a*c-n*c*c, b*c, k*k-b*b*d
      if c < 0
        a, b, c = -a, -b, -c
      end
      gcd = a.gcd(b).gcd(c)
      if gcd > 1
        a /= gcd
        b /= gcd
        c /= gcd
      end
    end
  }
end

if __FILE__ == $0
  each_pelleq_solutions(5) do |x, y|
    puts "#{x} #{y}"
  end
end
