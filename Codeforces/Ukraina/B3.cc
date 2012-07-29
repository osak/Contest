#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

int main() {
    int N, M, Y0, Y1;
    cin >> N >> M >> Y0 >> Y1;
    vector<int> mice(N);
    vector<int> cheeses(M);
    for(int i = 0; i < N; ++i) cin >> mice[i];
    for(int i = 0; i < M; ++i) cin >> cheeses[i];


    int ans = 0;
    vector<int> v(M, INT_MAX);
    for(int i = 0; i < N; ++i) {
        int p2 = lower_bound(cheeses.begin(), cheeses.end(), mice[i]) - cheeses.begin();
        int p1 = p2-1;
        int d1 = INT_MAX, d2 = INT_MAX;
        if(p2 < M) d2 = abs(mice[i]-cheeses[p2]);
        if(p1 >= 0) d1 = abs(mice[i]-cheeses[p1]);

        if(p2 == 0) {
            if(v[p2] == INT_MAX) ++ans;
            if(d2 < v[p2]) v[p2] = d2;
        }
        else if(p2 == M) {
            if(v[p1] == INT_MAX) ++ans;
            if(d1 < v[p1]) v[p1] = d1;
            else if(d1 == v[p1]) ++ans;
        }
        else {
            if(d1 < d2) {
                if(v[p1] == INT_MAX) ++ans;
                if(d1 < v[p1]) v[p1] = d1;
                else if(v[p1] == d1) ++ans;
            }
            else if(d1 > d2) {
                if(v[p2] == INT_MAX) ++ans;
                if(d2 < v[p2]) v[p2] = d2;
            }
            else {
                if(v[p1] == d1 || v[p1] == INT_MAX) {
                    ++ans;
                    v[p1] = d1;
                }
                else {
                    v[p2] = d2;
                    ++ans;
                }
            }
        }
    }
    cout << N-ans << endl;
    
    return 0;
}
