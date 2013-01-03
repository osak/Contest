#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

const int MOD = 314159265;
typedef unsigned long long ULL;

template <class T>
struct SegmentTree/*{{{*/
{
    vector<T> nodes;
    int D;
    SegmentTree(int size, int d) : D(d) {
        nodes.resize(size*2, T(0,0));
    }

    // [left, right) に対するクエリ．
    // 現在のノードはpos で， [pl, pr) を表わしている．
    T get_inner(int left, int right, int pos, int pl, int pr) {
        //cout << left << ' ' << right << ' ' << pos << ' ' <<  pl << ' ' << pr << endl;
        if(pr <= left || right <= pl) return make_pair(0,0); // 交差しない
        if(left <= pl && pr <= right) return nodes[pos]; // 完全に含まれる

        const int center = (pl+pr) / 2;
        T lv = get_inner(left, right, pos*2+1, pl, center);
        T rv = get_inner(left, right, pos*2+2, center, pr);
        T res(max(lv.first, rv.first), 0);
        if(lv.first >= D) {
            res.first = lv.first;
            res.second += lv.second;
        }
        if(rv.first >= D) {
            res.first = max(res.first, rv.first);
            res.second += rv.second;
        }
        return res;
    }

    T get(int left, int right) {
        return get_inner(left, right, 0, 0, nodes.size()/2);
    }

    T set_inner(int left, int right, int pos, int pl, int pr, const T &val) {
        //cout << left << ' ' << right << ' ' << pos << ' ' <<  pl << ' ' << pr << endl;
        if(pr <= left || right <= pl) return nodes[pos]; // 交差しない
        //if(left <= pl && pr <= right) return nodes[pos] += pr-pl; // 完全に含まれる
        if(pl+1 == pr) return nodes[pos] = val;

        const int center = (pl+pr)/2;
        T lv = set_inner(left, right, pos*2+1, pl, center, val);
        T rv = set_inner(left, right, pos*2+2, center, pr, val);
        nodes[pos] = T(max(lv.first, rv.first),0);
        else if(lv.first < rv.first) return nodes[pos] = rv;
        return nodes[pos] = T(lv.first, (lv.second+rv.second) % MOD);
    }

    T set(int left, int right, const T &val) {
        return set_inner(left, right, 0, 0, nodes.size()/2, val);
    }
};/*}}}*/

void quantize(vector<pair<int,int> > &segments, const set<int> &num_list) {
    map<int,int> dict;
    int id = 0;
    for(set<int>::const_iterator it = num_list.begin(); it != num_list.end(); ++it) {
        dict[*it] = id++;
    }
    for(vector<pair<int,int> >::iterator it = segments.begin(); it != segments.end(); ++it) {
        it->first = dict[it->first];
        it->second = dict[it->second];
    }
}

// comb[n] = n C D
int comb[100001];
vector<vector<int> > memo(2, vector<int>(16, 0));
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N, D;
    cin >> N >> D;

    // n C (D-1) のテーブルを作る
    const int TAKE = D-1;
    memo[0][0] = 1;
    for(int i = 1; i <= TAKE; ++i) {
        memo[0][i] = memo[0][i-1]*(TAKE-i+1) / i;
    }
    comb[TAKE] = memo[0][TAKE];
    for(int i = TAKE+1; i <= 100000; ++i) {
        vector<int> &prev = memo[0];
        vector<int> &cur = memo[1];
        cur[0] = 1;
        for(int j = 1; j <= TAKE; ++j) {
            cur[j] = (prev[j-1]+prev[j]) % MOD;
        }
        comb[i] = cur[TAKE];
        //cout << i << ' ' << comb[i] << endl;
        prev.swap(cur);
    }
    vector<pair<int,int> > segments;
    set<int> num_list;
    for(int i = 0; i < N; ++i) {
        int l, r;
        cin >> l >> r;
        segments.push_back(make_pair(l, r));
        num_list.insert(l);
        num_list.insert(r);
    }
    sort(segments.begin(), segments.end());
    quantize(segments, num_list);

    int ans = 0;
    SegmentTree<pair<int,int> > st(131072);
    for(int i = 0; i < N; ++i) {
        const pair<int,int> &range = segments[i];
        pair<int,int> max_tag = st.get(range.second+1, 2*N);
        //cout << max_tag.first << ' ' << max_tag.second << endl;
        max_tag.first++;
        if(max_tag.first >= D) {
            ULL tmp = comb[max_tag.first-1];
            tmp *= max_tag.second;
            ans += tmp % MOD;
            ans %= MOD;
        }
        if(max_tag.second == 0) max_tag.second = 1;
        st.set(range.second, range.second+1, max_tag);
    }
    cout << ans << endl;
    return 0;
}
