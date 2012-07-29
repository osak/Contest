#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

struct Comp {
    bool operator ()(const pair<int,int> &a, const pair<int,int> &b) const {
        return (double)a.second/a.first > (double)b.second/b.first;
    }
};

int main() {
    int N, W;
    cin >> N >> W;

    vector<pair<int,int> > v;
    for(int i = 0; i < N; ++i) {
        int w, vn;
        cin >> w >> vn;
        v.push_back(make_pair(w, vn));
    }
    sort(v.begin(), v.end(), Comp());

    double ans = 0;
    double rem = W;
    for(vector<pair<int,int> >::iterator it = v.begin(); it != v.end(); ++it) {
        if(it->first > rem) {
            ans += it->second * rem / it->first;
        }
        else {
            ans += it->second;
            rem -= it->first;
        }
    }

    cout << ans << endl;
    return 0;
}
