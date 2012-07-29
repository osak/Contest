//Name: Nails
//Level: 3
//Category: DP,動的計画法
//Note:

/*
 * ある釘から何段下までが囲まれるかを持ってDP．
 * 三角形の形より，ひとつの釘からは必ず左下と右下に領域が広がる．
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Triangle {
    int a, b, x;
    bool operator <(const Triangle &other) const {
        return a < other.a;
    }
};

bool update(int &a, int v) {
    if(a > v) return false;
    a = v;
    return true;
}

int dp[2][5000];
int main() {
    int N, M;
    cin >> N >> M;
    vector<Triangle> triangles(M);
    for(int i = 0; i < M; ++i) {
        Triangle &t = triangles[i];
        cin >> t.a >> t.b >> t.x;
    }
    sort(triangles.begin(), triangles.end());

    int ans = 0;
    int ptr = 0;
    vector<Triangle>::iterator it = triangles.begin();
    dp[ptr][0] = -1;
    for(int i = 0; i < N; ++i) {
        int np = 1-ptr;
        while(it != triangles.end() && it->a-1 == i) {
            update(dp[ptr][it->b-1], it->x);
            ++it;
        }
        for(int j = 0; j < N; ++j) {
            dp[np][j] = -1;
        }
        for(int j = 0; j <= i; ++j) {
            if(dp[ptr][j] != -1) {
                ++ans;
                update(dp[np][j], dp[ptr][j]-1);
                if(j+1 < N) update(dp[np][j+1], dp[ptr][j]-1);
            }
        }
        ptr = np;
    }
    cout << ans << endl;
    return 0;
}
