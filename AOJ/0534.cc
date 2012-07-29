#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int sim(const vector<int> &v, int start) {
    int l = start, r = start+1;
    while(true) {
        int pl = l, pr = r;
        int color = v[l];
        while(l >= 0 && v[l] == color) --l;
        while(r < v.size() && v[r] == color) ++r;
        if(pl-l + r-pr < 4) {
            l = pl;
            r = pr;
            break;
        }
    }
    return l+1 + v.size()-r;
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<int> v(N);
        for(int i = 0; i < N; ++i) {
            cin >> v[i];
        }
        int ans = N+100;
        for(int i = 0; i < N; ++i) {
            v[i] = 1+v[i]%3;
            ans = min(ans, sim(v, i));
            v[i] = 1+v[i]%3;
            ans = min(ans, sim(v, i));
            v[i] = 1+v[i]%3;
        }
        cout << ans << endl;
    }
    return 0;
}
    

