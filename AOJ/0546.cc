#include <iostream>
#include <set>
#include <vector>
#include <cstdlib>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    while(true) {
        int N, K;
        cin >> N >> K;
        if(!N && !K) break;

        vector<string> cards(N);
        for(int i = 0; i < N; ++i) {
            cin >> cards[i];
        }
        int pos[] = {0,1,2,3};
        set<int> made;
        while(true) {
            vector<int> arr(&pos[0], &pos[K]);
            do {
                string str;
                for(int i = 0; i < K; ++i) {
                    str += cards[arr[i]];
                }
                int n = atoi(str.c_str());
                made.insert(n);
            } while(next_permutation(arr.begin(), arr.end()));

            ++pos[K-1];
            for(int i = K-1; i >= 0; --i) {
                if(pos[i] >= N-(K-i-1)) {
                    if(i > 0) ++pos[i-1];
                    pos[i] = -1;
                }
                else break;
            }
            /*
            cout << "pos[0]: " << pos[0] << endl;
            cout << "pos[1]: " << pos[1] << endl;
            cout << "pos[2]: " << pos[2] << endl;
            */
            if(pos[0] == -1) break;
            for(int i = 1; i < K; ++i) {
                if(pos[i] != -1) continue;
                pos[i] = pos[i-1]+1;
            }
        }
        cout << made.size() << endl;
    }
    return 0;
}
