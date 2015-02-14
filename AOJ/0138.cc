//Name: Track and Field Competition
//Level: 1
//Category: やるだけ
//Note: 

/**
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void calc(vector<pair<double,int>> &v) {
    sort(begin(v), end(v));
    cout << v[0].second << ' ' << v[0].first << endl;
    cout << v[1].second << ' ' << v[1].first << endl;
}

bool solve(bool first) {
    vector<pair<double,int>> v(8), rem;
    for(int i = 0; i < 3; ++i) {
        for(int i = 0; i < 8; ++i) {
            cin >> v[i].second >> v[i].first;
        }
        calc(v);
        rem.insert(end(rem), begin(v)+2, end(v));
    }
    calc(rem);
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(2);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
