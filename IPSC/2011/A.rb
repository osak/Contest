#Infinity
#geti,getia
#Object # dcopy
#
#String # to_a
#   "abc".to_a #=> ["a","b","c"]
#String # to_ia
#   "1 2 3".to_ia #=> [1,2,3]
#
#Array # rsort,rsort!
#   [1,3,2,4].rsort #=> [4,3,2,1]
#
#Integer # divisor
#   24.divisor #=> [1,2,3,4,6,8,12,24]
#
include Math
require "prime"
require "bigdecimal"
require "bigdecimal/math"
require "matrix"
require "pp"
require "benchmark"

Infinity = 1/0.0
class Matrix;def inspect;empty? ? "Matrix.empty(#{row_size}, #{column_size})":"Matrix[\n#{@rows.map(&:inspect).join("\n")}\n]";end;end
def pbin(obj);case obj;when Integer;puts obj.to_s(2);end;end
class String;def to_a;split("");end;end
class String;def to_ia;split.map(&:to_i);end;end
def getia;gets.to_ia;end
def geti;gets.to_i;end
class Object;def dcopy;Marshal.load(Marshal.dump(self));end;end
class Array;def rsort;sort.reverse;end;def rsort!;sort!.reverse!;end;end

n = geti
hh = {
    "scissors"  => ["paper","lizard"],
    "paper"     => ["rock","Spock"],
    "rock"      => ["scissors","lizard"],
    "lizard"    => ["paper","Spock"],
    "Spock"     => ["rock","scissors"]
}
before = nil
n.times do
    hand = gets.chomp
    if hh[hand][0] == before
        before = hh[hand][1]
    else
        before = hh[hand][0]
    end
    puts before
end
