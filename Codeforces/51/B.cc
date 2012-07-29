#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef unsigned long long ULL;

int main() {
    vector<ULL> n_(4);
    vector<char> op_(3);

    for(int i = 0; i < 4; ++i) cin >> n_[i];
    for(int i = 0; i < 3; ++i) cin >> op_[i];

    sort(n_.begin(), n_.end());
    sort(op_.begin(), op_.end());
    ULL ans = 1000*1000*1000*1000ULL;
    do { 
        do {
            int i = 0;
            vector<ULL> n = n_;
            vector<char> op = op_;
            while(i < 3) {
                if(op[i] == '*') {
                    n[i] *= n[i+1];
                    for(int j = i+1; j < 3; ++j) n[j] = n[j+1];
                    for(int j = i; j < 2; ++j) op[j] = op[j+1];
                    n[3] = 0;
                    op[2] = '\0';
                }
                else ++i;
            }
            i = 0;
            while(i < 3) {
                if(op[i] == '+') {
                    n[i] += n[i+1];
                    for(int j = i+1; j < 3; ++j) n[j] = n[j+1];
                    for(int j = i; j < 2; ++j) op[j] = op[j+1];
                    n[3] = 0;
                    op[2] = '\0';
                }
                else ++i;
            }
            ans = min(ans, n[0]);
        } while(next_permutation(op_.begin(), op_.end()));
    } while(next_permutation(n_.begin(), n_.end()));


    cout << ans << endl;

    return 0;
}
