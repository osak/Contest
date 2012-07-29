#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<pair<int, int> > stones;
        for(int i = 1; i <= N; ++i) {
            int c;
            cin >> c;
            if(stones.empty()) stones.push_back(make_pair(c, 1));
            else {
                if(i % 2 == 0) {
                    if(stones.back().first == c) ++stones.back().second;
                    else {
                        stones.back().first = c;
                        ++stones.back().second;
                        if(stones.size() >= 2) {
                            stones[stones.size()-2].second += stones.back().second;
                            stones.pop_back();
                        }
                    }
                }
                else {
                    if(stones.back().first == c) ++stones.back().second;
                    else stones.push_back(make_pair(c, 1));
                }
            }
        }
        int sum = 0;
        for(int i = 0; i < stones.size(); ++i) {
            if(stones[i].first == 0) sum += stones[i].second;
        }
        cout << sum << endl;
    }
    return 0;
}
