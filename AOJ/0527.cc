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
                        for(int j = stones.size()-1; j >= 0; --j) {
                            if(stones[j].first == c) break;
                            stones[j].first = c;
                        }
                        ++stones.back().second;
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
