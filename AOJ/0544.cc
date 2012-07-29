#include <iostream>
#include <vector>

using namespace std;

int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<int> v(N);
        int pos = 0;
        for(int i = 0; i < N; ++i) {
            cin >> v[i];
        }
        vector<int> m(M);
        for(int i = 0; i < M; ++i) {
            cin >> m[i];
        }
        for(int i = 0; i < M; ++i) {
            pos += m[i];
            if(pos >= N-1) {
                cout << (i+1) << endl;
                break;
            }
            pos += v[pos];
            if(pos >= N-1) {
                cout << (i+1) << endl;
                break;
            }
        }
    }
    return 0;
}
