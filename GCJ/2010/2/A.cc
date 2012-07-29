#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;


int main() {
    int cases;
    cin >> cases;
    for(int C = 1; C <= cases; ++C) {
        int n;
        cin >> n;

        vector<vector<int> > diamond(n);
        for(int i = 0; i < n*2+1; ++i) {
            int limit = (i>n) ? i+1 : (n*2-i)-1;
            for(int j = 0; j < i+1; ++j) {
                int k;
                cin >> k;
                diamond[i].push_back(k);
            }
        }

        for(int 
    }
}
