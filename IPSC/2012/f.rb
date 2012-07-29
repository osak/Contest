#!/usr/bin/ruby

gets.to_i.times do
  gets
  n = gets.to_i
  probs = gets.split.map(&:to_f)

  ans = 0
  (1..n).each do |i|
    probs.combination(i) do |comb|
      indices = (0...i).to_a.freeze

      prob = 0
      face_cnt = 1
      while face_cnt <= i
        pr = 0
        cnt = 0
        indices.combination(face_cnt) do |sub|
          subprob = 1
          i.times do |idx|
            if sub.index(idx)
              subprob *= comb[idx]
            else
              subprob *= (1.0-comb[idx])
            end
          end
          pr += subprob
          cnt += 1
        end
        #puts "#{face_cnt} #{i} #{pr}"
        prob += pr
        face_cnt += 2
      end
      #puts prob

      if (prob-0.5).abs < 1e-12
        ans += 1
      end
    end
  end

  puts ans
end
