# 4
#0123
# 5
class Dice
    def initialize(arr)
        @arr = arr.dup
    end

    def rot_x
        @arr[0], @arr[1..3] = @arr[3], @arr[0..2]
    end

    def rot_y
        @arr[4], @arr[2], @arr[5], @arr[0] = @arr[2], @arr[5], @arr[0], @arr[4]
    end

    def rot_z
        @arr[4], @arr[1], @arr[5], @arr[3] = @arr[1], @arr[5], @arr[3], @arr[4]
    end

    def to_a
        @arr.dup
    end
end

arr = gets.chomp.each_char.sort
dict = []
cnt = 0
arr.permutation do |perm|
    dice = Dice.new(perm)
    ok = true
    catch(:check) {
        6.times do |t|
            4.times do
                if dict.index(dice.to_a)
                    ok = false
                    throw :check
                end
                dice.rot_x
            end
            if t == 3
                dice.rot_y
                dice.rot_z
            elsif t == 4
                dice.rot_z
                dice.rot_z
            else
                dice.rot_y
            end
        end
    }
    if ok
        cnt += 1
        dict << dice.to_a
    end
end

p cnt
