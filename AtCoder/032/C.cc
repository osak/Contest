//Name: 仕事計画
//Level: 3
//Category: 区間スケジューリング,辞書順最小,復元,貪欲法,Greedy,動的計画法,DP
//Note: 

/**
 * 順番を気にしない区間スケジューリング問題であれば、終点の早い順にソートして貪欲に取っていけばよい。
 * 今回は辞書順最小という制約があるので、もう一歩進める必要がある。
 *
 * 一般に、こういう形式の問題では
 * ・順番を気にしない状態での最適解（区間数）を求める
 * ・使うノードを先頭から決定していく。ノードを1つ加えたとき、最適解が実現可能かどうかを判定し、実現可能であれば採用する。
 * という二段階の構成になる。
 * 2段階目がO(N)かかるので、今回の制約では最適解の実現可能性をO(1)で判定する必要がある。
 *
 * ここで、普通の区間スケジューリング問題を考えたとき、ある区間を必ず使うとしたとき、それより後にいくつの区間が使えるかは一意に定まることに注目する。
 * これは前処理として、SegmentTree等のデータ構造を使えばO(N log N)、DPっぽくやればO(N + max(b_i))ですべての区間について求めることができる
 * （以下のコードでは後者の方法を使っている）。
 * あとは、「いくつの区間が使えるか」から対応する区間を逆引きできるようにしておき、1つずつ選んでいけばよい。
 *
 * オーダーは O(N log N + max(b_i))。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>
#include <set>

using namespace std;

struct Task {
    int idx;
    int cnt;
    int a, b;

    bool operator <(const Task &t) const {
        return b < t.b;
    }
};

bool solve(bool first) {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<Task> v(N);
    for(int i = 0; i < N; ++i) {
        v[i].idx = i;
        v[i].cnt = 0;
        cin >> v[i].a >> v[i].b;
    }
    sort(begin(v), end(v));
    vector<int> dp(v.back().b+2);
    dp.back() = 0;
    int prev = (int)dp.size() - 1;
    for(int i = N-1; i >= 0; --i) {
        for(int t = prev-1; t >= v[i].b; --t) {
            dp[t] = max(dp[t+1], dp[t]);
        }
        v[i].cnt = dp[v[i].a] = max(dp[v[i].a], dp[v[i].b] + 1);
        prev = v[i].b;
    }
    for(int t = prev-1; t >= 0; --t) {
        dp[t] = max(dp[t+1], dp[t]);
    }

    const int taskcnt = *max_element(begin(dp), end(dp));
    vector<set<pair<int,int>>> task_by_cnt(taskcnt+1);
    for(int i = 0; i < N; ++i) {
        task_by_cnt[v[i].cnt].insert(make_pair(v[i].idx, i));
    }
    vector<int> ans;
    int lastt = 0;
    for(int i = taskcnt; i > 0; --i) {
        auto &ti = task_by_cnt[i];
        for (auto t : ti) {
            if(v[t.second].a >= lastt) {
                ans.push_back(t.second);
                lastt = v[t.second].b;
                break;
            }
        }
    }
    assert(ans.size() == taskcnt);
    cout << taskcnt << endl;
    for(int i = 0; i < taskcnt; ++i) {
        if(i > 0) cout << ' ';
        cout << v[ans[i]].idx+1;
    }
    cout << endl;

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
