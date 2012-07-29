#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for(int CASE = 1; CASE <= T; ++CASE) {
        int N;
        cin >> N;
        vector<vector<int> > levels(N, vector<int>(2));
        for(int i = 0; i < N; ++i) {
            cin >> levels[i][0] >> levels[i][1];
        }
        int goal = 0;
        for(int i = 0; i < N; ++i) {
            goal *= 3;
            goal += 2;
        }

        vector<int> memo(590490, INT_MAX);
        priority_queue<pair<int, int> > q;
        q.push(make_pair(0, 0));
        while(!q.empty()) {
            int cost = -q.top().first;
            int state = q.top().second;
            q.pop();

            //cout << state << endl;
            if(memo[state] < cost) continue;
            memo[state] = cost;
            if(state == goal) break;

            int stars = 0;
            vector<int> rating(N, 0);
            {
                int tmp = state;
                for(int i = 0; i < N; ++i) {
                    int r = tmp % 3;
                    stars += r;
                    tmp /= 3;
                    rating[i] = r;
                    //cout << r << ' ';
                }
                //cout << endl;
            }
            for(int i = 0; i < N; ++i) {
                if(rating[i] == 2) continue;

                int nc = cost+1;
                int ns = 0;
                for(int j = N-1; j >= 0; --j) {
                    ns *= 3;
                    if(j == i) {
                        int nr = 2;
                        for(; nr > rating[i]; --nr) {
                            if(levels[i][nr-1] <= stars) break;
                        }
                        ns += nr;
                    }
                    else ns += rating[j];
                }
                //cout << "ns " << ns << endl;
                if(memo[ns] > nc) {
                    memo[ns] = nc;
                    q.push(make_pair(-nc, ns));
                }
            }
        }
                
        cout << "Case #" << CASE << ": ";
        if(memo[goal] == INT_MAX) {
            cout << "Too Bad";
        }
        else {
            cout << memo[goal];
        }
        cout << endl;
    }

    return 0;
}
