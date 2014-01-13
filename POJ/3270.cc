//Name: Cow Sorting
//Level: 3
//Category: 数学,Math,貪欲,Greedy
//Note:

/**
 * 入れ替えであるから、巡回置換の組に分けて考えればよい。
 *
 * ある巡回置換を元の順に並べ替えるとき、その置換に含まれる数だけでもっとも効率が良いのは、
 * 一番小さい数を次々と移動させながら正しい場所に正しい数を移動させていく方法である。
 * これにより、(置換に含まれる数の和) + 最小の数 ✕ (置換の長さ-2) のコストで置換の整列ができる。
 * また、さらにコストを小さくする方法として、全体で一番小さい数を置換の中で一番小さい数とあらかじめ入れ替えることにより、
 * (置換に含まれる数の和) + 全体で最小の数 ✕ (置換の長さ-1 + 2) + 置換内最小の数 のコストを達成でき、こちらのほうが小さくなる可能性もある。
 * これらを両方試し、小さい方を採用していけばよい。
 *
 * オーダーはO(N log N)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <numeric>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

typedef long long LL;

int arr[10000];
int pos_of[10000];
LL rev_dict[10000];

LL calc(int pos) {
    static vector<LL> v;
    v.clear();
    int cur = pos;
    while(arr[cur] != cur) {
        v.push_back(cur);
        arr[pos_of[cur]] = arr[cur];
        arr[cur] = cur;
        cur = pos_of[cur];
    }
    v.push_back(cur);
    int minval = *min_element(v.begin(), v.end());
    const int N = v.size();
    LL acc = 0;
    TIMES(i, N) {
        acc += rev_dict[v[i]];
    }
    //printf("%lld\n", acc);
    if(minval == 0) {
        return acc + rev_dict[minval] * ((int)v.size()-2);
    } else {
        LL a = rev_dict[minval] * ((int)v.size()-2);
        LL b = rev_dict[0] * ((int)v.size()+1) + rev_dict[minval];
        //return acc + a;
        return acc + min(a, b);
    }
}

bool solve() {
    int N;
    if(scanf("%d", &N) == EOF) return false;
    if(!N) return false;

    map<int,int> dict;
    TIMES(i, N) {
        scanf("%d", &arr[i]);
        dict[arr[i]] = 0;
    }
    {
        int idx = 0;
        for(map<int,int>::iterator it = dict.begin(); it != dict.end(); ++it) {
            it->second = idx++;
            rev_dict[it->second] = it->first;
        }
    }

    TIMES(i, N) {
        arr[i] = dict[arr[i]];
        pos_of[arr[i]] = i;
    }
    LL ans = 0;
    TIMES(i, N) {
        if(arr[i] != i) {
            ans += calc(i);
        }
        /*
        TIMES(j, N) {
            printf("%d ", rev_dict[arr[j]]);
        }
        puts("");
        */
    }
    printf("%lld\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
