#include <iostream>
#include <vector>

using namespace std;

struct Stick {
    int p, q, r, b;
    Stick() {}
    Stick(int pp, int qq, int rr, int bb) : p(pp), q(qq), r(rr), b(bb) {}
};

int gcd(int a, int b) {
    if(a < b) return gcd(b, a);
    while(true) {
        int tmp = a % b;
        a = b;
        b = tmp;
        if(b == 0) break;
    }
    return a;
}

int dfs(vector<Stick> &sticks, int pos) {
    int wr = 1, wb = 1;
    if(sticks[pos].r != 0) wr = dfs(sticks, sticks[pos].r);
    if(sticks[pos].b != 0) wb = dfs(sticks, sticks[pos].b);

    int mr = wr*sticks[pos].p;
    int mb = wb*sticks[pos].q;
    int g = gcd(mr, mb);
    return wr*(mb/g) + wb*(mr/g);
}

int main() {
    while(true) {
        int n;
        cin >> n;
        if(!n) break;

        vector<Stick> sticks(n+1);
        vector<bool> is_child(n+1, false);
        for(int i = 0; i < n; ++i) {
            int p, q, r, b;
            cin >> p >> q >> r >> b;
            sticks[i+1] = Stick(p, q, r, b);
            is_child[r] = is_child[b] = true;
        }

        int start = 1;
        while(is_child[start]) ++start;
        cout << dfs(sticks, start) << endl;
    }
    return 0;
}
