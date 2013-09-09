module GaloisField
  def self.[](modulo)
    @@cache ||= {}
    @@cache[modulo] ||= create_impl(modulo)
  end

  def self.create_impl(modulo)
    cls = Class.new(Numeric)
    cls.instance_eval do
      const_set(:MODULO, modulo)
      include GaloisNumberImpl
    end
    name = "GaloisNumber_#{modulo}"
    const_set(name.intern, cls)
    cls
  end

  module GaloisNumberImpl
    def initialize(num)
      unless num.is_a?(Integer)
        raise TypeError.new("Galois numbers can be created only from integer value.")
      end
      @value = num % self.class::MODULO
    end

    def +(other)
      self.class.new((@value + other.to_i) % self.class::MODULO)
    end

    def -(other)
      self.class.new((@value - other.to_i + self.class::MODULO) % self.class::MODULO)
    end

    def *(other)
      self.class.new((@value * other.to_i) % self.class::MODULO)
    end

    def /(other)
      self * other.inv
    end

    def inv
      res = 1
      pow = @value
      rem = self.class::MODULO-2
      while rem > 0
        if rem.odd?
          res *= pow
          res %= self.class::MODULO
        end
        pow *= pow
        pow %= self.class::MODULO
        rem /= 2
      end
      res.to_galois(self.class::MODULO)
    end

    def coerce(val)
      if val.is_a?(Integer)
        [val.to_galois(self.class::MODULO), self]
      else
        super
      end
    end

    def to_i
      @value
    end

    def to_s
      @value.to_s
    end

    def inspect
      "#{@value}(mod #{self.class::MODULO})"
    end
  end
end

class Integer
  def to_galois(modulo)
    GaloisField[modulo].new(self)
  end
end

if __FILE__ == $0
  puts 32.to_galois(10)
  a = 10.to_galois(31)
  b = 9.to_galois(31)
  c = 8.to_galois(20)
  puts a / b
  puts a.inspect
  puts c.inspect
end
