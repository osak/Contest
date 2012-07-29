//Name: Icicles
//Level: 2
//Category: シミュレーション
//Note:

/*
 * つららがどれか折れるまで，伸びているつららの集合は変化しない．
 * したがって，つららが折れる時刻をイベントとして時間順に処理していく．
 * つららが折れた場合，影響を受けるつららはその両隣のみであることに注意．
 */
#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

inline bool check(const vector<int> &icicles, int pos) {
    const int N = (int)icicles.size();
    if(pos < 0 || pos >= N) return false;
    if(icicles[pos] == 0) return false;
    bool left = pos>0 ? icicles[pos-1] < icicles[pos] : true;
    bool right = pos+1<N ? icicles[pos+1] < icicles[pos] : true;
    return left && right;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, L;
    cin >> N >> L;
    vector<int> icicles(N);
    for(int i = 0; i < N; ++i) {
        cin >> icicles[i];
    }
    int ans = 0;
    priority_queue<pair<int,int> > q;
    for(int i = 0; i < N; ++i) {
        if(check(icicles, i)) {
            int t = L - icicles[i];
            q.push(make_pair(-t, i));
        }
    }
    while(!q.empty()) {
        int t = -q.top().first;
        int pos = q.top().second;
        q.pop();
        ans = t;

        icicles[pos] = 0;
        if(check(icicles, pos-1)) {
            int nt = t + L - icicles[pos-1];
            q.push(make_pair(-nt, pos-1));
        }
        if(check(icicles, pos+1)) {
            int nt = t + L - icicles[pos+1];
            q.push(make_pair(-nt, pos+1));
        }
    }
    cout << ans << endl;
    return 0;
}
