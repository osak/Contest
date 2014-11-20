//Name: Surf Smelt Fishing Contest
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;

    int winner, winner_v = -1;
    for(int i = 0; i < N; ++i) {
        int a, v;
        cin >> a >> v;
        if(v > winner_v || (v == winner_v && a < winner)) {
            winner = a;
            winner_v = v;
        }
    }
    cout << winner << ' ' << winner_v << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
