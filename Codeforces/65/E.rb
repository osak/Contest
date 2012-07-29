class E
    ATOMS = "H  He  Li  Be      B   C   N   O   F   Ne Na  Mg      Al  Si  P   S   Cl  Ar K   Ca      Sc  Ti  V   Cr  Mn  Fe  Co  Ni  Cu  Zn  Ga  Ge  As  Se  Br  Kr Rb  Sr      Y   Zr  Nb  Mo  Tc  Ru  Rh  Pd  Ag  Cd  In  Sn  Sb  Te  I   Xe Cs  Ba      La  Ce  Pr  Nd  Pm  Sm  Eu  Gd  Tb  Dy  Ho  Er  Tm  Yb    Lu  Hf  Ta  W   Re  Os  Ir  Pt  Au  Hg  Tl  Pb  Bi  Po  At  Rn Fr  Ra Ac  Th  Pa  U   Np  Pu  Am  Cm  Bk  Cf  Es  Fm  Md  No".split

    def initialize
        @atom_num = {}
        ATOMS.each_with_index { |v, i| @atom_num[v] = i+1 }
    end

    def dfs(pats, cur, curpat, idx)
        return if @memo[idx][curpat]

        if pats.size == idx
            puts "YES"
            cur.each_with_index do |equ, idx|
                atoms = []
                @srcs.each_with_index do |v, i|
                    atoms << ATOMS[v-1] if equ&(1<<i) != 0
                end
                puts "#{atoms.join('+')}->#{ATOMS[@dests[idx]-1]}"
            end
            exit
        end
        pats[idx].each do |pat|
            dfs(pats, cur+[pat], curpat|pat, idx+1) if curpat&pat == 0
        end
        @memo[idx][curpat] = true
    end


    def solve
        n,k = gets.split.map(&:to_i)
        @srcs = gets.split.map { |v| @atom_num[v] }
        @dests = gets.split.map { |v| @atom_num[v] }

        pats = []
        @dests.each do |dest|
            arr = Array.new(dest+1) { Array.new }
            arr[0] = [0]
            1.upto(dest) do |i|
                @srcs.each_with_index do |src, idx|
                    prev = i - src
                    next if prev < 0
                    arr[prev].each do |pat|
                        next if pat&(1<<idx) != 0
                        arr[i] << (pat | (1<<idx))
                    end
                end
                arr[i].uniq!
            end
            pats << arr[dest]
        end
        @memo = Array.new(pats.size) { Hash.new }
        dfs(pats, [], 0, 0) if pats.all? {|v| !v.empty? }
        puts "NO"
    end
end

e = E.new
e.solve
