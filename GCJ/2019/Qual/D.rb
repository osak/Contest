#!/usr/bin/env ruby

Segment = Struct.new(:start, :end, :broken)

def build_test_pattern(segments)
  fragments = []
  segments.each do |segment|
    mid = (segment.start + segment.end) / 2
    fragments << '0' * (mid - segment.start)
    fragments << '1' * (segment.end - mid)
  end
  fragments.join
end

def consume(segment, pattern, response, ptr)
  sent_pattern = pattern[segment.start...segment.end]
  sent_zeros = sent_pattern.count('0')
  sent_ones = sent_pattern.count('1')

  response_pattern = response[ptr, segment.end - segment.start - segment.broken]
  response_zeros = response_pattern.count('0')
  response_ones = response_pattern.count('1')

  broken_zeros = sent_zeros - response_zeros
  broken_ones = sent_ones - response_ones

  new_segments = [
      Segment.new(segment.start, segment.start + sent_zeros, broken_zeros),
      Segment.new(segment.start + sent_zeros, segment.end, broken_ones)
  ]
  new_ptr = ptr + response_pattern.length
  [new_segments, new_ptr]
end

t = gets.to_i
(1..t).each do |cn|
  n, b, f = gets.split.map(&:to_i)

  segments = [Segment.new(0, n, b)]
  while segments.size < n
    pattern = build_test_pattern(segments)

    #STDERR.puts pattern
    puts pattern
    STDOUT.flush
    response = gets.chomp
    #STDERR.puts "res " + response

    ptr = 0
    next_segments = []
    segments.each do |segment|
      new_segments, ptr = consume(segment, pattern, response, ptr)
      next_segments.push(*new_segments)
    end
    segments = next_segments
  end

  broken_ids = segments.select{|s| s.broken > 0}.map(&:start)
  puts "#{broken_ids.join(' ')}"
  STDOUT.flush

  result = gets.to_i
  STDERR.puts "Case ##{cn}: #{broken_ids} #{result}"
end


