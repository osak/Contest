int main() {
    int N = (int)Stdio.stdin->gets();
    array(int) lamps = allocate(N+1);
    array(string) init = Stdio.stdin->gets() / " ";
    for(int i = 0; i < N; ++i) {
        if(init[i] == "on") lamps[i+1] = 1;
    }

    int M = (int)Stdio.stdin->gets();
    array(int) keys = (array(int))(Stdio.stdin->gets() / " ");
    mapping(int:int) cnt = Array.count(keys);
    array(int) ks = indices(cnt);

    for(int i = 0; i < sizeof(ks); ++i) {
        int k = ks[i];
        if(cnt[k] % 2 == 0) continue;
        for(int j = k; j <= N; j += k) {
            lamps[j] ^= 1;
        }
    }

    for(int i = 1; i <= N; ++i) {
        if(i != 1) write(" ");
        write(lamps[i] ? "on" : "off");
    }
    write("\n");
    return 0;
}
