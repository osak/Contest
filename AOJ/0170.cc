//Name: Lunch
//Level: 2
//Category: 全探索
//Note:

/*
 * 全ての置き方を試し，条件を満たすもののうち重心が一番低いものを選ぶ．
 *
 * オーダーはO(N!)．
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

struct Tag {
    string f;
    int w, s;
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N;
        cin >> N;
        if(!N) break;
        vector<Tag> foods(N);
        for(int i = 0; i < N; ++i) {
            cin >> foods[i].f >> foods[i].w >> foods[i].s;
        }
        vector<int> order(N);
        for(int i = 0; i < N; ++i) {
            order[i] = i;
        }
        vector<int> best_ans;
        double best_G = 1e30;
        do {
            int sum_w = 0;
            int sum_gw = 0;
            bool ok = true;
            for(int i = N-1; i >= 0; --i) {
                if(sum_w > foods[order[i]].s) {
                    ok = false;
                    break;
                }
                sum_w += foods[order[i]].w;
                sum_gw += foods[order[i]].w * (i+1);
            }
            if(ok) {
                double G = static_cast<double>(sum_gw) / sum_w;
                if(G < best_G) {
                    best_ans = order;
                    best_G = G;
                }
            }
        } while(next_permutation(order.begin(), order.end()));
        for(int i = 0; i < N; ++i) {
            cout << foods[best_ans[i]].f << endl;
        }
    }
    return 0;
}
