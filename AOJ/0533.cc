#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    for(int i = 0; i < 2; ++i) {
        vector<int> v;
        for(int j = 0; j < 10; ++j) {
            int n;
            cin >> n;
            v.push_back(n);
        }
        sort(v.begin(), v.end());
        reverse(v.begin(), v.end());
        cout << v[0]+v[1]+v[2] << (i==0?' ':'\n');
    }
    return 0;
}
