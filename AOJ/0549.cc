//Name: A Traveler
//Level: 2
//Category: シミュレーション
//Note:

/*
 * 宿場町1から各宿場町までの距離を累積和として求めておくと，任意の宿場町間の距離がO(1)で出せる．
 * あとはシミュレーションするだけ．
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    cin >> N >> M;
    vector<int> distance(N-1); // distance of town_i between town_{i+1}
    vector<int> accum(N-1, 0);
    for(int i = 0; i < N-1; ++i) {
        cin >> distance[i];
        if(i > 0) accum[i] = accum[i-1];
        accum[i] += distance[i];
    }
    int ans = 0;
    int cur = 0;
    for(int i = 0; i < M; ++i) {
        int d;
        cin >> d;
        int next = cur+d;
        if(d > 0) {
            int cur_acc = cur==0 ? 0 : accum[cur-1];
            ans += accum[next-1] - cur_acc;
        }
        else {
            int next_acc = next==0 ? 0 : accum[next-1];
            ans += accum[cur-1] - next_acc;
        }
        ans %= 100000;
        cur = next;
    }
    cout << ans << endl;
    return 0;
}
