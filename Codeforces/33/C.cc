#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> v(N);
    int total = 0;
    for(int i = 0; i < N; ++i) {
        cin >> v[i];
        total += v[i];
    }

    vector<int> prefix(N), suffix(N+1);
    vector<pair<int, int> > prefix_list(N);
    vector<pair<int, int> > suffix_list(N+1);

    prefix[0] = -v[0];
    prefix_list[0] = make_pair(prefix[0], 0);
    for(int i = 1; i < N; ++i) {
        prefix[i] = prefix[i-1]-v[i];
        prefix_list[i] = make_pair(prefix[i], i);
    }
    prefix_list.push_back(make_pair(0, -1));

    suffix[N] = 0;
    suffix_list[N] = make_pair(suffix[N], N);
    for(int i = N-1; i >= 0; --i) {
        suffix[i] = suffix[i+1]-v[i];
        suffix_list[i] = make_pair(suffix[i], i);
    }

    sort(prefix_list.begin(), prefix_list.end());
    reverse(prefix_list.begin(), prefix_list.end());
    sort(suffix_list.begin(), suffix_list.end());
    reverse(suffix_list.begin(), suffix_list.end());

    int ans = total;
    int pp = 0;
    for(int i = N; i >= 0; --i) {
        while(prefix_list[pp].second >= i) ++pp;
        int tmp = suffix[i] + prefix_list[pp].first;
        ans = max(ans, total+tmp*2);
    }

    int sp = 0;
    for(int i = 0; i < N; ++i) {
        while(suffix_list[sp].second <= i) ++sp;
        int tmp = prefix[i] + suffix_list[sp].first;
        ans = max(ans, total+tmp*2);
    }

    cout << ans << endl;
    return 0;
}
