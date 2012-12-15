//Name: Joseph's Potato
//Level: 1
//Category: シミュレーション,やるだけ
//Note:

#include <iostream>
#include <vector>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;
        vector<int> players(N);
        for(int i = 0; i < N; ++i) players[i] = i+1;
        int pos = N-1;
        for(int phase = 0; phase < N-1; ++phase) {
            const int SIZE = players.size();
            pos = (pos+M) % SIZE;
            players.erase(players.begin()+pos);
            --pos;
        }
        cout << players.front() << endl;
    }
    return 0;
}
