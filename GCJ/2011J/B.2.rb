#Mi_Sawa
#
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
#geti
#getia
#
#sample_case{}
#   input from      #{$Problem}-sample.in
#   compare with    #{$Problem}-sample.out
#small_case{}
#   input from      #{$Problem}-small-attempt\d+.in
#   output to       #{$Problem}-small-attempt\d+.out
#large_case{}
#   input from      #{$Problem}-large.in
#   output to       #{$Problem}-large.out
#stdin_case{}
#   input from      STDIN
#   output to       STDOUT
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
def small_case
    files=Dir.glob("./#{$Problem}-small-attempt*.in")
    input_file=File.new(files.sort[-1],"r")
    output_file=File.new(files.sort[-1].sub("in","out"),"w")
    $stdin=input_file
    1.upto(geti){|cas|output_file.puts"Case ##{cas}: #{yield}"}
end
def large_case
    input_file=File.new("#{$Problem}-large.in","r")
    output_file=File.new("#{$Problem}-large.out","w")
    $stdin=input_file
    1.upto(geti){|cas|output_file.puts"Case ##{cas}: #{yield}"}
end
def sample_case
    input_file=File.new("#{$Problem}-sample.in","r")
    $stdin=input_file
    expect=File.new("#{$Problem}-sample.out","r").read.split(/Case #\d+: /)
    expect.shift
    expect.map!{|s|s.chomp("")}
    1.upto(geti){|cas|
        print "Test Case ##{cas}..."
        case_start=$stdin.pos
        receive=yield.to_s
        case_end=$stdin.pos
        if expect[cas-1] == receive
            puts "PASSED"
        else
            puts "FAILED","Input:"
            $stdin.pos=case_start
            puts gets until $stdin.pos == case_end
            puts "Expected:",expect[cas-1],"Received:",receive,nil
        end
    }
end
def stdin_case
    1.upto(geti){|cas|puts"Case ##{cas}: #{yield}"}
end
def small_practice_case
    input_file=File.new("#{$Problem}-small-practice.in","r")
    output_file=File.new("#{$Problem}-small-practice.out","w")
    $stdin=input_file
    1.upto(geti){|cas|output_file.puts"Case ##{cas}: #{yield}"}
end
def large_practice_case
    input_file=File.new("#{$Problem}-large-practice.in","r")
    output_file=File.new("#{$Problem}-large-practice.out","w")
    $stdin=input_file
    1.upto(geti){|cas|output_file.puts"Case ##{cas}: #{yield}"}
end

$Problem = $PROGRAM_NAME.split("/").last.split(".").first
$Problem = 'A' if $Problem.length != 1
#small_practice_case{
#large_practice_case{
#stdin_case{
#small_case{
large_case{
#sample_case{
    n, k = getia
    cts = []
    n.times do
        cts << getia
        cts[-1][1] -= 1
    end
    cts.sort_by!{|a|a[2]}
    res = 0
    memo = [[0, k-1]]
    until memo.empty? || cts.empty?
        c,t,s = cts.pop
        nex = []
        until memo.empty?
            rng = memo.pop
            if t < rng[0] || c.zero?#期限切れorコーヒー無し
                nex << rng.dcopy
            elsif rng[1] <= t#範囲内では期限切れにならない
                if rng[1] - rng[0] + 1 <= c #範囲内全部
                    c -= rng[1] - rng[0] + 1
                    res += (rng[1] - rng[0] + 1)*s
                else    #コーヒー全部
                    rng[1] -= c
                    res += c * s
                    nex << rng.dcopy
                    c = 0
                end
            else#範囲内で期限切れになる→範囲分割
                nex << [t+1, rng[1]].dcopy
                memo << [rng[0], t].dcopy
            end
        end
        memo = nex.dcopy
        memo.sort_by!{|a|a[0]}
    end
    res
}



