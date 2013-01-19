//Name: Eleven Puzzle
//Level: 3
//Category: 両側探索
//Note:

/*
 * 20手まで調べればよいので，初期状態から10手以内に到達可能な盤面を全て記憶し，
 * 完成状態から10手以内に到達可能な盤面との積集合を取って，最短到達手数を考える
 * いわゆる両側探索をすればよい．
 * 1つの盤面から遷移可能な盤面の個数は，それぞれの空白は最大で4箇所からカードが
 * スライドしてくる可能性があるため最大で 4*2 = 8個．
 * ただし，直前の盤面に戻るものは考えなくて良いため，実質遷移は7通り．
 * これを10手分列挙すると 7^10 = 約3億状態だが，実際には重複を多く含んでいたり，
 * 7通りも遷移がなかったりするためもっと小さくなる．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tr1/unordered_map>

using namespace std;

#define FOREACH(var,v) for(__typeof(v.begin()) var = v.begin(); var != v.end(); ++var)

const int NEIGHBOR[13][4] = {
    {2, -1, -1, -1},
    {2, 5, -1, -1},
    {0, 1, 3, 6},
    {2, 7, -1, -1},
    {5, -1, -1, -1},
    {1, 4, 6, 9},
    {2, 5, 7, 10},
    {3, 6, 8, 11},
    {7, -1, -1, -1},
    {5, 10, -1, -1},
    {6, 9, 11, 12},
    {7, 10, -1, -1},
    {10, -1, -1, -1}
};
typedef tr1::unordered_map<long long,int> CacheType;
int field[13];

long long encode() {
    long long res = 0;
    for(int i = 0; i < 13; ++i) {
        res *= 12;
        res += field[i];
    }
    return res;
}

void decode(long long code, int *blank) {
    int *ptr = blank;
    for(int i = 12; i >= 0; --i) {
        field[i] = code % 12;
        if(field[i] == 0) {
            *ptr = i;
            ++ptr;
        }
        code /= 12;
    }
}

struct NullCallback {
    void operator()(long long, int) const {}
};
struct AnsCallback {
    CacheType *cache;
    int ans;
    AnsCallback(CacheType *c) : cache(c), ans(100) {}

    void operator()(long long code, int step) {
        CacheType::const_iterator it = cache->find(code);
        if(it != cache->end()) {
            ans = min(ans, step + it->second);
        }
    }
};

template <class T>
void search(CacheType &cache, T &callback) {
    vector<long long> q[2];
    {
        long long code = encode();
        q[0].push_back(code);
        cache[code] = 0;
        callback(code, 0);
    }
    for(int step = 1; step <= 10; ++step) {
        q[1].clear();
        int buf[2];

        FOREACH(it, q[0]) {
            decode(*it, buf);
            for(int j = 0; j < 2; ++j) {
                const int blank = buf[j];
                for(int dir = 0; dir < 4; ++dir) {
                    if(NEIGHBOR[blank][dir] == -1) break;
                    swap(field[blank], field[NEIGHBOR[blank][dir]]);
                    long long code = encode();
                    CacheType::const_iterator cit = cache.find(code);
                    if(cit == cache.end()) {
                        q[1].push_back(code);
                        cache[code] = step;
                    }
                    swap(field[blank], field[NEIGHBOR[blank][dir]]);
                }
            }
        }
        sort(q[1].begin(), q[1].end());
        q[1].erase(unique(q[1].begin(), q[1].end()), q[1].end());
        q[0].swap(q[1]);
        FOREACH(it, q[0]) {
            callback(*it, step);
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(true) {
        for(int i = 0; i < 13; ++i) {
            cin >> field[i];
        }
        if(field[0] == -1) break;

        CacheType c1, c2;
        NullCallback nc;
        search(c1, nc);

        for(int i = 1; i <= 11; ++i) {
            field[i] = i;
        }
        field[0] = field[12] = 0;
        AnsCallback ac(&c1);
        search(c2, ac);
        if(ac.ans > 20) cout << "NA" << endl;
        else cout << ac.ans << endl;
    }
    return 0;
}
