#include <iostream>
#include <set>
#include <vector>
#include <tr1/unordered_set>

using namespace std;
using namespace tr1;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    vector<int> history;
    unordered_set<int> pair_sum;
    int ans = 0;
    for(int i = 0; i < N; ++i) {
        int ai;
        cin >> ai;
        for(vector<int>::const_iterator it = history.begin(); it != history.end(); ++it) {
            if(pair_sum.count(ai - *it) > 0) {
                ++ans;
                break;
            }
        }
        for(vector<int>::const_iterator it = history.begin(); it != history.end(); ++it) {
            pair_sum.insert(ai + *it);
        }
        pair_sum.insert(ai*2);
        history.push_back(ai);
    }
    cout << ans << endl;
    return 0;
}
