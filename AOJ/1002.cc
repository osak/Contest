#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int T;
    cin >> T;

    while(T--) {
        int N;
        string s;
        cin >> N >> s;

        vector<int> subcnt(N+1, 0);

        for(int i = 0; i < 2*N; ++i) 
            if(s[i] == 'Y') subcnt[(i+1)/2] |= 0x01;
        for(int i = 2*N; i < 4*N; ++i) 
            if(s[i] == 'Y') subcnt[(i+1)/2-N] |= 0x02;

        int cost = N;
        int pos = 0;
        while(subcnt[pos] == 0) ++pos;
        if(subcnt[pos] & 0x02) cost += 2;
        else cost += 1;

        int lastpat = subcnt[pos];
        for(++pos; pos < N+1; ++pos) {
            if(subcnt[pos] & 0x01) cost += 1;
            if(subcnt[pos] & 0x02) cost += 1;
            if(subcnt[pos]) lastpat = subcnt[pos];
        }
        cost += 1;

        if(lastpat & 0x01) cost -= 1;
        if(lastpat == 0) cost = N;

        cout << cost << endl;
    }
    return 0;
}
