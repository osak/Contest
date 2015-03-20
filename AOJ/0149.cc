//Name: Eye Test
//Level: 1
//Category: やるだけ
//Note:

/**
 * 表を写して引けば良い。
 */
#include <iostream>

using namespace std;

bool solve(bool first) {
    int res[2][4] = {0};
    double s[2];
    while(cin >> s[0] >> s[1]) {
        for(int i = 0; i < 2; ++i) {
            if(s[i] >= 1.1) {
                res[i][0]++;
            } else if(s[i] >= 0.6) {
                res[i][1]++;
            } else if(s[i] >= 0.2) {
                res[i][2]++;
            } else {
                res[i][3]++;
            }
        }
    }
    for(int i = 0; i < 4; ++i) {
        std::cout << res[0][i] << ' ' << res[1][i] << std::endl;
    }
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
