//Name: When Can We Meet?
//Level: 2
//Category: やるだけ
//Note:

/*
 * それぞれの日について、参加可能な人数をmapで保持しておく。
 *
 * オーダーは O(NM)。
 */
#include <iostream>
#include <unordered_map>

using namespace std;

bool solve() {
    int N, Q;
    if(!(cin >> N >> Q)) return false;
    if(!N && !Q) return false;

    unordered_map<int,int> m;
    for(int i = 0; i < N; ++i) {
        int M;
        cin >> M;
        for (int j = 0; j < M; ++j) {
            int v;
            cin >> v;
            m[v]++;
        }
    }

    int ans = 0;
    int ans_cnt = 0;
    for (auto e : m) {
        if(e.second >= Q && e.second >= ans_cnt) {
            if(ans == 0 || e.second > ans_cnt || e.first < ans) {
                ans = e.first;
                ans_cnt = e.second;
            }
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
