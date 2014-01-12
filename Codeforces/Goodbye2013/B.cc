//Name: New Year Present
//Level: 2
//Category: 貪欲,Greedy
//Note:

/**
 * 左から右へ歩きながら1つずつ落とし、戻りながら1つずつ落とし……を繰り返していく。
 * 最大で300✕300歩進み、コインも300✕300枚落とすことになるので、十分に制約に収まる。
 * オーダーはO(NS)。
 * ただしS = ∑a_i。
#include <iostream>
#include <vector>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;

    vector<int> wallet(N, 0);
    int done = 0;
    for(int i = 0; i < N; ++i) {
        cin >> wallet[i];
        if(wallet[i] == 0) ++done;
    }
    int cur = 0;
    int dir = -1;
    while(done != N) {
        if(wallet[cur] > 0) {
            cout << 'P';
            if(--wallet[cur] == 0) ++done;
        }
        if(cur == 0 || cur == N-1) dir *= -1;
        cout << (dir == 1 ? 'R' : 'L');
        cur += dir;
    }
    cout << endl;
    return true;
}
    
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
