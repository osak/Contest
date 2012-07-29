#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<int, int> duration;

int calc(int start, int end) {
    return (end/100-start/100)*60 + end%100-start%100;
}

int main() {
    while(true) {
        int N, P, Q;
        cin >> N >> P >> Q;
        if(!N && !P && !Q) break;

        vector<duration> v;

        for(int i = 0; i < N; ++i) {
            int M;
            cin >> M;
            duration d;
            d.first = P;
            cin >> d.second;
            v.push_back(d);
            for(int j = 0; j < M-1; ++j) {
                cin >> d.first >> d.second;
                v.push_back(d);
            }
            cin >> d.first;
            d.second = Q;
            v.push_back(d);
        }

        sort(v.begin(), v.end());

        int start = v[0].first, end = v[0].second;
        int ans = 0;
        for(int i = 1; i < v.size(); ++i) {
            if(v[i].first > end) {
                ans = max(ans, calc(start, end));
                start = v[i].first;
                end = v[i].second;
            }
            if(start < v[i].second) end = max(end, v[i].second);
        }
        ans = max(ans, calc(start, end));
        cout << ans << endl;
    }
    return 0;
}
