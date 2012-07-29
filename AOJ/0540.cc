#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>

using namespace std;

int main() {
    while(true) {
        int N, M, H, K;
        cin >> N >> M >> H >> K;
        if(!N && !M && !H && !K) break;
        
        vector<int> scores;
        vector<int> goals;
        vector<pair<int, int> > swaps;

        for(int i = 0; i < N; ++i) {
            int s;
            cin >> s;
            scores.push_back(s);
            goals.push_back(i);
        }

        vector<pair<int, int> > bars;
        for(int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            --a;
            bars.push_back(make_pair(b, a));
        }
        sort(bars.begin(), bars.end());
        for(int i = 0; i < M; ++i) {
            int a = bars[i].second;
            swaps.push_back(make_pair(goals[a], goals[a+1]));
            //cout << "swap " << goals[a] << ' ' << goals[a+1] << endl;
            swap(goals[a], goals[a+1]);
        }

        vector<int> to_goal(N);
        for(int i = 0; i < N; ++i) {
            to_goal[goals[i]] = i;
        }

        int ans = INT_MAX;
        int sum = 0;
        for(int i = 0; i < K; ++i) {
            sum += scores[to_goal[i]];
        }
        ans = sum;
        for(int i = 0; i < M; ++i) {
            int a = swaps[i].first;
            int b = swaps[i].second;
            if(a < K && b < K) continue;
            if(a >= K && b >= K) continue;

            int minus = (a<K) ? scores[to_goal[a]] : scores[to_goal[b]];
            int plus = (a<K) ? scores[to_goal[b]] : scores[to_goal[a]];
            int tmp = sum-minus+plus;
            ans = min(ans, tmp);
        }
        cout << ans << endl;
    }
}
