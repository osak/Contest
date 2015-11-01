class GaloisNumber < Numeric
  def self.modulo=(val)
    @@modulo = val.to_i
  end

  def initialize(num)
    @value = num.to_i % @@modulo
  end

  def +(other)
    GaloisNumber.new((@value + other.to_i) % @@modulo)
  end

  def -(other)
    GaloisNumber.new((@value - other.to_i + @@modulo) % @@modulo)
  end

  def *(other)
    GaloisNumber.new((@value * other.to_i) % @@modulo)
  end

  def coerce(val)
    if val.is_a?(Integer)
      [GaloisNumber.new(val), self]
    else
      super
    end
  end

  def to_i
    @value
  end

  def to_s
    @value
  end

  def inspect
    "#{@value}(mod #{@@modulo})"
  end
end

class Integer
  def to_galois
    GaloisNumber.new(self)
  end
end

