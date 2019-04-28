class SD
  SIZE = 10

  def initialize(arr)
    @arr = arr
    @sqrt = [0] * (arr.size / SIZE + 1)
    @arr.each_with_index do |v, i|
      if v > @sqrt[i/SIZE]
        @sqrt[i/SIZE] = v
      end
    end
  end

  def range_max(a, b)
    min_bin = (a / SIZE) + 1
    max_bin = (b / SIZE)
    max = @sqrt[min_bin...max_bin].max || 0
    (a...(min_bin*10)).each do |i|
      break if i >= @arr.size
      break if i >= b
      max = @arr[i] if @arr[i] > max
    end

    upper_start = [a, max_bin*10].max
    (upper_start...b).each do |i|
      break if i >= @arr.size
      next if i < a
      max = @arr[i] if @arr[i] > max
    end
    max
  end
end

t = gets.to_i
(1..t).each do |cn|
  n, k = gets.split.map(&:to_i)
  cs = gets.split.map(&:to_i)
  ds = gets.split.map(&:to_i)

  csd = SD.new(cs)
  dsd = SD.new(ds)

  ans = 0
  (0...n).each do |l|
    (l+1..n).each do |r|
      c = csd.range_max(l, r)
      d = dsd.range_max(l, r)
      if (c-d).abs <= k
        ans += 1
      end
    end
  end
  puts "Case ##{cn}: #{ans}"
end
