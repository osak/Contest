#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>

using namespace std;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for(int CASE = 1; CASE <= T; ++CASE) {
        int N, D;
        cin >> N;
        vector<pair<int,int> > vines(N);
        for(int i = 0; i < N; ++i) {
            cin >> vines[i].first >> vines[i].second;
        }
        cin >> D;

        bool ans = false;
        vector<int> most_far_from(N, INT_MAX);
        most_far_from[0] = 0;
        for(int i = 0; i < N; ++i) {
            const int dist = min(vines[i].second, vines[i].first - most_far_from[i]);
            //cout << i << ' ' << dist << endl;
            if(vines[i].first + dist >= D) {
                ans = true;
                break;
            }
            for(int j = i; j < N; ++j) {
                if(vines[j].first <= vines[i].first + dist) {
                    if(most_far_from[j] > vines[i].first) {
                        most_far_from[j] = vines[i].first;
                    }
                }
            }
        }

        cout << "Case #" << CASE << ": " << (ans?"YES":"NO") << endl;
    }

    return 0;
}
