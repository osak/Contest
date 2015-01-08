//Name: Doctor's Strange Particles
//Level: 2
//Category: 全探索
//Note: 

/**
 * 一番上の行に対する照射方法を固定すると、それより下の行が全て一意に決まる。
 * したがって、一番上の行だけを全探索してシミュレーションすればよい。
 *
 * オーダーは O(2^W HW)。
 */
#include <iostream>
#include <array>

using namespace std;

array<int,1<<10> eff;

bool solve(bool first) {
    array<int,10> f;
    for(int r = 0; r < 10; ++r) {
        f[r] = 0;
        for(int c = 0; c < 10; ++c) {
            int v;
            cin >> v;
            f[r] |= (v << c);
        }
    }

    array<int,10> ans;
    for(int pat = 0; pat < (1<<10); ++pat) {
        int prev = f[0] ^ eff[pat];
        int pmask = pat;
        ans[0] = pat;
        for(int r = 1; r < 10; ++r) {
            ans[r] = prev;
            const int tmp = f[r] ^ eff[prev] ^ pmask;
            pmask = prev;
            prev = tmp;
        }
        if(prev == 0) break;
    }
    for(int r = 0; r < 10; ++r) {
        for(int c = 0; c < 10; ++c) {
            if(c > 0) cout << ' ';
            cout << !!(ans[r] & (1<<c));
        }
        cout << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    for(int pat = 0; pat < (1<<10); ++pat) {
        eff[pat] = pat;
        for(int c = 0; c < 10; ++c) {
            if(pat & (1<<c)) {
                if(c > 0) eff[pat] ^= (1<<(c-1));
                if(c < 9) eff[pat] ^= (1<<(c+1));
            }
        }
    }

    bool first = true;
    int N;
    cin >> N;
    while(N-- && solve(first)) {
        first = false;
    }
    return 0;
}
