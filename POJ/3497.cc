//Name: Assemble
//Level: 3
//Category: 二分探索
//Note:

/**
 * 最小値の最大化なので、qualityについて二分探索。
 * 使えるqualityの下限を決め、もっとも安いパーツだけを買っていき、予算に収まるかを確かめれば良い。
 *
 * オーダーは O(N log N)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

struct Tag {
    int type, price, quality;

    Tag() {}
    Tag(int t, int p, int q) : type(t), price(p), quality(q) {}
};

vector<Tag> parts[1000];
map<string,int> t_dict;

void solve() {
    int N, B;
    scanf("%d %d", &N, &B);
    t_dict.clear();
    vector<int> q_list;
    TIMES(_, N) {
        static char type_[30];
        int p, q;
        scanf("%s %*s %d %d", type_, &p, &q);
        const string type(type_);
        if(t_dict.count(type) == 0) {
            const int id = t_dict.size();
            t_dict[type] = id;
            parts[id].clear();
        }
        parts[t_dict[type]].push_back(Tag(t_dict[type], p, q));
        q_list.push_back(q);
    }
    sort(q_list.begin(), q_list.end());
    q_list.erase(unique(q_list.begin(), q_list.end()), q_list.end());

    const int M = t_dict.size();
    long long left = 0, right = q_list.size();
    while(left+1 < right) {
        const int lim_idx = (left+right) / 2;
        const long long lim = q_list[lim_idx];
        long long sum = 0;
        TIMES(i, M) {
            long long min_price = B+1;
            const int K = parts[i].size();
            TIMES(j, K) {
                if(parts[i][j].quality < lim) continue;
                min_price = min(min_price, (long long)parts[i][j].price);
            }
            sum += min_price;
            if(sum > B) break;
        }
        if(sum <= B) {
            left = lim_idx;
        } else {
            right = lim_idx;
        }
    }
    
    printf("%d\n", q_list[left]);
}

int main() {
    int N;
    scanf("%d", &N);
    while(N--) solve();
    return 0;
}
