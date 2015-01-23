//Name: Stray Cats, Run...
//Level: 4
//Category: 最大値最小化,二分探索,Binary search,貪欲,Greedy
//Note: 

/**
 * 最大値の最小化なので、最大値について二分探索する。
 *
 * 最初にすべての餌入れに餌を入れるものとする。
 * このとき、最大値を超えて集まっている餌入れがあった場合、その餌入れは使わないようにしないと解消できない。
 * したがって、その餌入れを除いて再配置する。
 * これを繰り返し、条件を満たすことができるかを試していく。
 *
 * 再配置はナイーブにやると O(NM) かかるが、あらかじめ猫がいる全ての点に対して、餌入れを近い順にソートしておくと
 * 1つの最大値についての計算全体で O(NM) にできる。
 *
 * N=0のケースに注意。
 *
 * オーダーは O((N^2 + NM) log MC)。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<long long,long long> P;

struct Cat {
    P pos;
    int c;
};

inline long long norm(const P &a, const P &b) {
    const auto dx = a.first - b.first;
    const auto dy = a.second - b.second;
    return dx*dx + dy*dy;
}

bool solve(bool first) {
    int N, M;
    if(!(cin >> N >> M)) return false;
    if(!N && !M) return false;

    vector<Cat> cats(N);
    long long cat_sum = 0;
    for(int i = 0; i < N; ++i) {
        long long x, y;
        int c;
        cin >> x >> y >> c;
        cats[i] = Cat{P(x, y), c};
        cat_sum += c;
    }

    vector<P> ps(M);
    for(int i = 0; i < M; ++i) {
        long long x;
        cin >> x;
        ps[i] = P(x, 0);
    }
    sort(begin(ps), end(ps));

    vector<vector<int>> ord(N);
    for(int i = 0; i < N; ++i) {
        vector<pair<long long,int>> v;
        for(int j = 0; j < M; ++j) {
            v.emplace_back(norm(cats[i].pos, ps[j]), j);
        }
        sort(begin(v), end(v));
        for(auto e : v) {
            ord[i].push_back(e.second);
        }
    }

    long long left = 0, right = cat_sum;
    vector<long long> buf(M, 0);
    while(left+1 < right) {
        const long long LIM = (left + right) / 2;
        vector<bool> avail(M, true);
        vector<int> cursor(N, 0);
        int remain = M;
        bool ok = false;
        while(!ok && remain > 0) {
            fill(begin(buf), end(buf), 0);
            for(int i = 0; i < N; ++i) {
                while(!avail[ord[i][cursor[i]]]) ++cursor[i];
                assert(cursor[i] < ord[i].size());
                const int dest = ord[i][cursor[i]];
                buf[dest] += cats[i].c;
            }
            ok = true;
            for(int i = 0; i < M; ++i) {
                if(buf[i] > LIM) {
                    avail[i] = false;
                    --remain;
                    ok = false;
                }
            }
        }
        if(ok) {
            right = LIM;
        } else {
            left = LIM;
        }
    }
    cout << right << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
