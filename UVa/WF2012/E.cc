//Name: Infiltration
//Level: 5
//Category: 探索
//Note:

/*
 * YUHAの解説を見た．
 *
 * 行列の各行の論理和を取って，全部1にすればよい．
 * このとき，対角成分はすべて1にしておいてよい．
 *
 * (a,b)か(b,a)のどちらかは必ず1が立っているので，全体として結構1が多い．
 * YUHAの解説によると，5つ以内で必ず題意を満たす組が取れるらしいので，最大数を決めて全探索する．
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>
#include <bitset>

using namespace std;

#define TIMES(i,n) for(int i=0; (i) < (n); ++(i))
#define FOREACH(it,v) for(typeof((v).begin()) it=(v).begin(); (it) != (v).end(); ++(it))

typedef bitset<75> Flag;

bool calc(int pos, const vector<Flag> &flags, vector<int> &buf, const Flag &flag, const int MAX) {
    const int N = flags.size();
    if((int)buf.size() == MAX || pos == N) {
        return (int)flag.count() == N;
    }
    for(int i = pos; i < N; ++i) {
        if((flags[i] & flag) != flags[i]) {
            buf.push_back(i);
            if(calc(i+1, flags, buf, flag | flags[i], MAX)) return true;
            buf.pop_back();
        }
    }
    return false;
}

vector<int> solve(const int N) {
    vector<Flag> flags(N);
    TIMES(i, N) {
        string pat;
        cin >> pat;
        TIMES(j, N) {
            if(pat[j] == '1') flags[i][j] = 1;
        }
        flags[i][i] = 1;
    }

    for(int use = 1; use <= N; ++use) {
        vector<int> buf;
        bool found = calc(0, flags, buf, Flag(), use);
        if(found) return buf;
    }
    assert(false);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    int cn = 1;
    while(cin >> N) {
        vector<int> res = solve(N);
        cout << "Case " << cn << ": " << res.size();
        FOREACH(it, res) {
            cout << " " << *it+1;
        }
        cout << endl;
        ++cn;
    }
    return 0;
}
