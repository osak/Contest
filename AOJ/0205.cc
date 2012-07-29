#include <iostream>
#include <vector>

using namespace std;

int main() {
    while(true) {
        vector<int> v(5, 0);
        vector<int> cnt(3, 0);
        for(int i = 0; i < 5; ++i) {
            cin >> v[i];
            if(v[i] == 0) return 0;
            v[i]--;
            cnt[v[i]]++;
        }

        if((cnt[0] > 0 && cnt[1] > 0 && cnt[2] > 0) || cnt[0] == 5 || cnt[1] == 5 || cnt[2] == 5) {
            for(int i = 0; i < 5; ++i) v[i] = 3;
        }
        else {
            for(int i = 0; i < 5; ++i) v[i] = cnt[(v[i]+1)%3]>0 ? 1 : 2;
        }

        for(int i = 0; i < 5; ++i) cout << v[i] << endl;
    }
    return 0;
}
