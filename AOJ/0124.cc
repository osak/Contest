//Name: League Match Score Sheet
//Level: 1
//Category: やるだけ
//Note: 

/**
 * 入力時に勝ち点を計算し、ソートする。
 *
 * オーダーは O(N log N)。
 */
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

bool solve(bool first) {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;
    if(!first) cout << endl;

    vector<pair<int,string>> vs;
    for(int i = 0; i < N; ++i) {
        string t;
        int w, l, e;
        cin >> t >> w >> l >> e;
        vs.emplace_back(w*3 + e, t);
    }
    stable_sort(begin(vs), end(vs), [](const pair<int,string> &a, const pair<int,string> &b){return a.first > b.first;});
    for (const auto &t : vs) {
        cout << t.second << "," << t.first << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) first = false;
    return 0;
}
