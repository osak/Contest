#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> v(N+1, 1);
    v[0] = 0;
    while(M--) {
        string to, the, dir, of;
        int idx;
        cin >> to >> the >> dir >> of >> idx;
        if(dir == "left") for(int i = idx; i <= N; ++i) v[i] = 0;
        else if(dir == "right") for(int i = 1; i <= idx; ++i) v[i] = 0;
    }
    int cnt = 0;
    for(int i = 0; i <= N; ++i) 
        if(v[i]) ++cnt;
    if(cnt == 0) cnt = -1;
    cout << cnt << endl;

    return 0;
}

