#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

def relax(field, h, nh)
  relaxed_rows = []
  relaxed_cols = []
  field.each_with_index do |row, ri|
    if row.all?{|elt| elt == h}
      relaxed_rows << ri
    end
  end
  field.transpose.each_with_index do |col, ci|
    if col.all?{|elt| elt == h}
      relaxed_cols << ci
    end
  end
  relaxed_rows.each do |ri|
    (0...field[0].size).each do |ci|
      field[ri][ci] = nh
    end
  end
  relaxed_cols.each do |ci|
    (0...field.size).each do |ri|
      field[ri][ci] = nh
    end
  end
end

solve do
  r, c = gets.split.map(&:to_i)
  field = []
  r.times do
    field << gets.split.map(&:to_i)
  end
  heights = field.flatten.sort.uniq
  catch(:failed) {
    (0...heights.size).each do |hi|
      relax(field, heights[hi], heights[hi+1])
      if field.flatten.index(heights[hi])
        throw :failed, "NO"
      end
    end
    "YES"
  }
end
