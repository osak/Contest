#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

typedef vector<int>::iterator Iterator;

int main() {
    ios::sync_with_stdio(0);

    string str;
    getline(cin, str);

    vector<vector<int> > accum(3, vector<int>(1, 0));

    int ans = 0;
    for(int i = 0; i < str.size(); ++i) {
        int idx = -1;
        switch(str[i]) {
            case 'J':
                idx = 0;
                break;
            case 'O':
                idx = 1;
                break;
            case 'I':
                idx = 2;
                break;
        }

        int len = 10000000;
        for(int j = 0; j < 3; ++j) {
            int next = accum[j][i];
            if(idx == j) next++;

            len = min(len, next);
            accum[j].push_back(next);
        }

        pair<int,int> cur = make_pair(0, i+1);
        for(int j = 0; j < 3; ++j) {
            int target = accum[j].back() - len;
            pair<Iterator,Iterator> bound = equal_range(accum[j].begin(), accum[j].end(), target);
            pair<int,int> range = make_pair(bound.first-accum[j].begin(), bound.second-accum[j].begin()-1);
            //cout << range.first << ' ' << range.second << endl;
            if(range.first > cur.first) {
                cur.first = range.first;
            }
            if(range.second < cur.second) {
                cur.second = range.second;
            }
        }
        //cout << "l" << i << ": " << len << ' ' << cur.first << ' ' << cur.second << endl;
        if(cur.first <= cur.second) {
            ans = max(ans, len);
        }
    }

    cout << ans << endl;

    return 0;
}
