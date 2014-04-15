#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

def naomi_war(naomi)
  naomi.pop
end

def naomi_decwar(naomi, ken)
  if naomi[0] > ken[0]
    # Pretend 1.0 if my smallest can beats ken's smallest
    naomi.shift
    1.0
  else
    # Force to use ken's largest by pretend my smallest as ken's next largest
    naomi.shift
    ken[-1] - 0.0001
  end
end

def ken_war(ken, v)
  idx = (0...ken.size).bsearch{|i| ken[i] > v}
  if idx
    kv = ken[idx]
    ken.delete_at(idx)
    kv
  else
    ken.shift
  end
end

solve do
  n = gets.to_i
  naomi = gets.split.map(&:to_f).sort.freeze
  ken = gets.split.map(&:to_f).sort.freeze

  # Deceitful war
  naomi_hand = naomi.dup
  ken_hand = ken.dup
  d_score = 0
  n.times do
    nv = naomi_decwar(naomi_hand, ken_hand)
    kv = ken_war(ken_hand, nv)
    if nv > kv
      d_score += 1
    end
  end

  # normal war
  naomi_hand = naomi.dup
  ken_hand = ken.dup
  n_score = 0
  n.times do
    nv = naomi_war(naomi_hand)
    kv = ken_war(ken_hand, nv)
    if nv > kv
      n_score += 1
    end
  end
  "#{d_score} #{n_score}"
end
