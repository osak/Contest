//Name: Tricky Function
//Level: 4
//Category: 最近点対
//Note:

/**
 * aを累積和に直すと、最小化したい関数は
 *   f(i,j) = (i-j)^2 + (S[j]-S[i])^2
 * となる。
 * これは、平方根を取るとユークリッド距離であるから、最近点対問題に帰着できる。
 *
 * オーダーは O(N (log N)^2)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;
const LL INF = 100000LL * 100000;

LL dist(const pair<LL,LL> &a, const pair<LL,LL> &b) {
    const LL x = a.first - b.first;
    const LL y = a.second - b.second;
    return x*x + y*y;
}

LL ans = INF;
void calc(int left, int right, const vector<pair<LL,LL>> &ps) {
    if(right - left <= 1) return;
    if(right - left == 2) {
        ans = min(ans, dist(ps[left], ps[left+1]));
        return;
    }
    const int mid = (left + right) / 2;
    calc(left, mid, ps);
    calc(mid, right, ps);
    int li = mid, ri = mid+1;
    const pair<LL,LL> &mp = ps[mid];
    vector<pair<LL,LL>> sub;
    while(li >= left && (mp.first-ps[li].first)*(mp.first-ps[li].first) <= ans) sub.push_back(ps[li--]);
    while(ri < right && (mp.first-ps[ri].first)*(mp.first-ps[ri].first) <= ans) sub.push_back(ps[ri++]);
    sort(sub.begin(), sub.end(), [](const pair<LL,LL> &a, const pair<LL,LL> &b){return a.second < b.second;});
    const int M = sub.size();
    for(int i = 0; i < M; ++i) {
        for(int j = i-1; j >= 0; --j) {
            if((sub[i].second - sub[j].second)*(sub[i].second - sub[j].second) > ans) break;
            ans = min(ans, dist(sub[i], sub[j]));
        }
    }
}

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    LL acc = 0;
    vector<pair<LL,LL>> ps;
    for(int i = 0; i < N; ++i) {
        LL v;
        cin >> v;
        acc += v;
        ps.push_back(make_pair(i+1, acc));
    }
    ans = INF;
    calc(0, N, ps);
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
