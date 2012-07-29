#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    int N;
    while(cin >> N && !cin.eof()) {
        vector<vector<int> > v(N, vector<int>(2));
        for(int i = 0; i < N; ++i) {
            int n;
            cin >> n;
            v[i][0] = n/10;
            v[i][1] = n%10;
        }

        int unpaired = N*2;
        for(int i = 0; i < N; ++i) {
            for(int k = 0; k < 2; ++k) {
                if(v[i][k] == -1) continue;
                for(int j = i+1; j < N; ++j) {
                    if(v[i][k] == v[j][0]) {
                        v[i][k] = v[j][0] = -1;
                        unpaired -= 2;
                        break;
                    }
                    else if(v[i][k] == v[j][1]) {
                        v[i][k] = v[j][1] = -1;
                        unpaired -= 2;
                        break;
                    }
                }
            }
        }

        if(unpaired <= 2) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}
