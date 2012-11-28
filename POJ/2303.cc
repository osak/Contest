//Name: Russian Dolls
//Level: 4
//Category: 動的計画法,DP,DAG,経路復元,Special Judge
//Note:

/*
 * マトリョーシカを作る問題は，高さと半径を2次元平面にプロットして右上から左下へDAGをたどっていくことで解ける．
 * ただしこの問題ではよくある最長経路，最短経路問題ではなく，全体を同じ大きさの2グループに分けた上で経路復元をしなければならない．
 *
 * 経路復元のためにDP表を考えると，必要な情報は
 * [Aの最後のノード][Bの最後のノード][Aの長さ][Bの長さ]
 * の4つ．
 * ここで，Bの長さは他の3つの情報から計算できるため，前3つだけを情報として使えばよい．
 * マトリョーシカは全て使われるため，あるマトリョーシカ m を加えるときの状態遷移は
 * ・[a][b][al] → [m][b][al+1]
 * ・[a][b][al] → [a][m][al]
 * のどちらかとなる．
 * 普通にDP表を埋めていくと 200*200*100*100 ループで間に合わないが，遷移可能な状態が少ないためこれらをsetで管理するとよい．
 *
 * オーダーは O(N^4)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

#define FOREACH(var,v) for(__typeof(v.begin()) var = v.begin(); var != v.end(); ++var)

struct Doll {
    int h, d, w;

    bool operator <(const Doll &other) const {
        if(h != other.h) return h < other.h;
        return d < other.d;
    }
};

struct Tag {
    int ai, bi, al;
    Tag() {}
    Tag(int a, int b, int l) : ai(a), bi(b), al(l) {}

    bool operator <(const Tag &other) const {
        if(ai != other.ai) return ai < other.ai;
        if(bi != other.bi) return bi < other.bi;
        return al < other.al;
    }
    
    bool operator ==(const Tag &other) const {
        return ai == other.ai && bi == other.bi && al == other.al;
    }
};

inline bool can(const Doll &a, const Doll &b) {
    return a.h <= b.h-2*b.w && a.d <= b.d-2*b.w;
}

// [atop][btop][alen]
bool dp[201][201][101];
Tag prev[201][201][101];

void setdp(int a, int b, int al) {
    dp[a+1][b+1][al] = true;
}

bool getdp(int a, int b, int al) {
    return dp[a+1][b+1][al];
}

void setprev(int a, int b, int al, const Tag &t) {
    prev[a+1][b+1][al] = t;
}

Tag getprev(int a, int b, int al) {
    return prev[a+1][b+1][al];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<Doll> dolls(2*N);
        for(int i = 0; i < 2*N; ++i) {
            Doll &d = dolls[i];
            cin >> d.h >> d.d >> d.w;
        }
        sort(dolls.begin(), dolls.end());
        reverse(dolls.begin(), dolls.end());
        for(int atop = 0; atop <= 2*N; ++atop) {
            for(int btop = 0; btop <= 2*N; ++btop) {
                for(int alen = 0; alen <= N; ++alen) {
                    dp[atop][btop][alen] = false;
                    prev[atop][btop][alen] = Tag(-1, -1, -1);
                }
            }
        }
        set<Tag> states;
        states.insert(Tag(-1, -1, 0));
        for(int di = 0; di < 2*N; ++di) {
            //cout << di << endl;
            set<Tag> next;
            FOREACH(it, states) {
                if(it->al < N && (it->ai == -1 || can(dolls[di], dolls[it->ai]))) {
                    //setdp(di, it->bi, it->al+1);
                    setprev(di, it->bi, it->al+1, *it);
                    //cout << "set " << di << ' ' << it->bi << ' ' << it->al+1 << endl;
                    next.insert(Tag(di, it->bi, it->al+1));
                }
                if(di - it->al < N && (it->bi == -1 || can(dolls[di], dolls[it->bi]))) {
                    //setdp(it->ai, di, it->al);
                    setprev(it->ai, di, it->al, *it);
                    //cout << "set " << it->ai << ' ' << di << ' ' << it->al << endl;
                    next.insert(Tag(it->ai, di, it->al));
                }
            }
            states.swap(next);
        }
        vector<int> va, vb;
        Tag anst;
        // There will always be a state that a's last node is 2N-1
        for(int bi = 0; bi < 2*N; ++bi) {
            if(getprev(2*N-1, bi, N).al != -1) {
                anst = Tag(2*N-1, bi, N);
                break;
            }
        }
        while(anst.al != -1) {
            //cout << anst.ai << ' ' << anst.bi << ' ' << anst.al << endl;
            if(anst.ai != -1 && (va.size() == 0 || anst.ai != va.back())) va.push_back(anst.ai);
            if(anst.bi != -1 && (vb.size() == 0 || anst.bi != vb.back())) vb.push_back(anst.bi);
            anst = getprev(anst.ai, anst.bi, anst.al);
        }
        reverse(va.begin(), va.end());
        reverse(vb.begin(), vb.end());
        FOREACH(it, va) {
            const Doll &d = dolls[*it];
            cout << d.h << ' ' << d.d << ' ' << d.w << endl;
        }
        cout << '-' << endl;
        FOREACH(it, vb) {
            const Doll &d = dolls[*it];
            cout << d.h << ' ' << d.d << ' ' << d.w << endl;
        }
        cout << endl;
    }
    return 0;
}
