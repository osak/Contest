//Name: Course Planning for Lazy Students
//Level: 3
//Category: 有向グラフ,探索
//Note:

/*
 * 1科目ずつ履修可能かどうかを確認しつつ幅優先探索で可能なパターンを探索していく．
 * 幅優先による枝刈りをせず，2^N通りの履修全てを試す方法ではTLEした．
 *
 * オーダーはどちらも O(N*2^N) だが，多くのケースでは最後まで探索する必要がないらしくこれで間に合う．
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Tag {
    int pat, value, cost;
    Tag(int p, int v, int c) : pat(p), value(v), cost(c) {}
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N, U;
        cin >> N >> U;
        if(!N && !U) break;

        vector<int> need_mask(N, 0);
        vector<int> value(N, 0);
        for(int i = 0; i < N; ++i) {
            int K;
            cin >> value[i] >> K;
            int mask = 0;
            while(K--) {
                int R;
                cin >> R;
                mask |= (1<<R);
            }
            need_mask[i] = mask;
        }
        int ans = N;
        vector<int> seen(1<<N, 0);
        queue<Tag> q;
        q.push(Tag(0, 0, 0));
        seen[0] = 1;
        while(!q.empty()) {
            Tag t = q.front();
            if(t.value >= U) {
                ans = t.cost;
                break;
            }
            q.pop();
            for(int i = 0; i < N; ++i) {
                if(!(t.pat & (1<<i)) && (t.pat & need_mask[i]) == need_mask[i]) {
                    int next_pat = t.pat | (1<<i);
                    if(!seen[next_pat]) {
                        seen[next_pat] = 1;
                        q.push(Tag(next_pat, t.value + value[i], t.cost + 1));
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
