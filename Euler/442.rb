#!/usr/bin/env ruby

# Aho-Corasick法のオートマトンを作って、その上の位置と何桁目にいるかの情報をもって、パターン数でDigit DP。

require 'memoize'
include Memoize

class Automaton
  class Node
    @@idx = 0
    attr_reader :index
    attr_accessor :terminal
    def initialize(root=self, terminal=false)
      @index = @@idx
      @@idx += 1
      @terminal = terminal
      @next = Hash.new{|h,k| h[k] = [root, false]}
    end

    def add_next(digit, node, strict=false)
      return nil if @next[digit][1]
      @next[digit] = [node, strict]
    end

    def next(digit)
      @next[digit].first
    end

    def terminal?
      @terminal
    end

    def strict?(digit)
      @next[digit][1]
    end
  end

  def initialize(strs)
    @trie = Node.new
    @pool = [@trie]
    strs.each do |str|
      append_trie(str)
    end
    loop do
      changed = false
      strs.each do |str|
        changed ||= build_automaton(str)
      end
      break if not changed
    end
    strs.each do |str|
      @pool.each do |start|
        cur = start
        catch(:end) {
          str.each_char do |c|
            throw :end if not cur.strict?(c.to_i)
            cur = cur.next(c.to_i)
          end
          cur.terminal = true
        }
      end
    end
    @trie.freeze
  end

  def root
    @trie
  end

  def append_trie(str)
    cur = root
    str.each_char do |c|
      digit = c.to_i
      n = cur.next(digit)
      if n == root
        n = Node.new(root)
        @pool << n
        cur.add_next(digit, n, true)
      end
      cur = n
    end
    cur.terminal = true
  end

  def build_automaton(str)
    cur = shadow = root
    changed = false
    str.each_char.with_index do |c, i|
      digit = c.to_i
      (0..9).each do |d|
        cur_next = cur.next(d)
        shadow_next = shadow.next(d)
        if cur_next != shadow_next
          changed ||= cur.add_next(d, shadow_next)
        end
      end
      cur = cur.next(digit)
      shadow = shadow.next(digit) if i > 0
    end
    changed
  end
end

def calc(pos, node)
  return 1 if pos == -1
  return 0 if node.terminal?
  res = 0
  (0..9).each do |digit|
    nx = node.next(digit)
    res += calc(pos-1, nx) if not nx.terminal?
  end
  #puts "#{pos} #{node} = #{res}"
  res
end
memoize :calc

TARGET = 10**18+1
#TARGET = 500000+1
pows = (1..20).map{|i| (11**i).to_s}
$automaton = Automaton.new(pows)
str = ""
pos = 20
node = $automaton.root
sum = 0
(0..20).reverse_each do |pos|
  (0..9).each do |digit|
    nx = node.next(digit)
    if not nx.terminal?
      pat_num = calc(pos-1, nx) 
      if sum + pat_num >= TARGET
        #puts "#{pos} #{digit} #{sum+pat_num}"
        str << digit.to_s
        node = nx
        break
      end
      sum += pat_num
    end
  end
end

puts str
