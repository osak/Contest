#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstdio>

using namespace std;

int main() {
    int N, K, T, U, V, L;
    cin >> N >> K >> T >> U >> V >> L;

    priority_queue<pair<int, int> > q;
    vector<int> v(N);
    for(int i = 0; i < N; ++i) {
        cin >> v[i];
        q.push(make_pair(-v[i], 1));
    }

    bool boost = false;
    int boost_dist = 0;
    int ignore = 0;
    int prev = 0;
    int carrots = 0;
    q.push(make_pair(-L, 2));
    while(!q.empty()) {
        int pos = -q.top().first;
        int type = q.top().second;
        q.pop();

        if(boost) {
            boost_dist += pos - prev;
        }
        prev = pos;

        if(type == 0) {
            if(ignore) {
                --ignore;
                continue;
            }

            if(carrots) {
                --carrots;
                q.push(make_pair(-(pos+V*T), 0));
            }
            else {
                boost = false;
            }
        }
        else if(type == 1) {
            if(boost) {
                if(carrots == K) {
                    q.push(make_pair(-(pos+V*T), 0));
                    ++ignore;
                }
                else {
                    ++carrots;
                }
            }
            else {
                q.push(make_pair(-(pos+V*T), 0));
                boost = true;
            }
        }
        else if(type == 2) {
            break;
        }

    }

    printf("%.7f\n", (double)boost_dist / V + (double)(L-boost_dist) / U);

    return 0;
}
