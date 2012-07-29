class E
    ATOMS = "Hoge H  He  Li  Be      B   C   N   O   F   Ne Na  Mg      Al  Si  P   S   Cl  Ar K   Ca      Sc  Ti  V   Cr  Mn  Fe  Co  Ni  Cu  Zn  Ga  Ge  As  Se  Br  Kr Rb  Sr      Y   Zr  Nb  Mo  Tc  Ru  Rh  Pd  Ag  Cd  In  Sn  Sb  Te  I   Xe Cs  Ba      La  Ce  Pr  Nd  Pm  Sm  Eu  Gd  Tb  Dy  Ho  Er  Tm  Yb    Lu  Hf  Ta  W   Re  Os  Ir  Pt  Au  Hg  Tl  Pb  Bi  Po  At  Rn Fr  Ra Ac  Th  Pa  U   Np  Pu  Am  Cm  Bk  Cf  Es  Fm  Md  No".split

    def initialize
        @atom_num = {}
        ATOMS.each_with_index { |v, i| @atom_num[v] = i }
    end

    def dfs(sp, dp, sum, using)
        if dp == @dests.size
            puts "YES"
            arr = Array.new(@dests.size){Array.new}
            using.each_with_index do |v, idx|
                arr[v] << @srcs[idx]
            end
            arr.each_with_index do |v, idx|
                puts "#{v.map{|a| ATOMS[a]}.join('+')}->#{ATOMS[@dests[idx]]}"
            end
            exit
        end

        prev = -1
        sp.upto(@srcs.size-1) do |i|
            next if @srcs[i] == prev
            next if using[i] != -1

            tot = sum + @srcs[i]
            next if tot > @dests[dp]

            using[i] = dp
            if tot == @dests[dp]
                dfs(0, dp+1, 0, using)
            else
                dfs(i+1, dp, tot, using)
            end
            using[i] = -1

            prev = @srcs[i]
        end
    end


    def solve
        n,k = gets.split.map(&:to_i)
        @srcs = gets.split.map { |v| @atom_num[v] }.sort
        @dests = gets.split.map { |v| @atom_num[v] }

        dfs(0, 0, 0, [-1]*@srcs.size)
        puts "NO"
    end
end

e = E.new
e.solve
