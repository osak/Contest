//Name: Vampirish Night
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <vector>

using namespace std;

int main() {
    while(true) {
        int N, K;
        cin >> N >> K;
        if(!N && !K) break;

        vector<int> s(K);
        for(int i = 0; i < K; ++i) cin >> s[i];
        bool ok = true;
        while(N--) {
            for(int i = 0; i < K; ++i) {
                int b;
                cin >> b;
                s[i] -= b;
                if(s[i] < 0) ok = false;
            }
        }
        cout << (ok?"Yes":"No") << endl;
    }
    return 0;
}
