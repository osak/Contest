#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int W, N;
    cin >> W >> N;

    vector<int> v;
    for(int i = 1; i <= W; ++i) v.push_back(i);
    while(N--) {
        int a, b;
        char c;
        cin >> a >> c >> b;
        swap(v[a-1], v[b-1]);
    }
    for(int i = 0; i < v.size(); ++i) cout << v[i] << endl;
    return 0;
}
