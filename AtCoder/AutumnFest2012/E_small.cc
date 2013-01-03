#include <iostream>
#include <vector>

using namespace std;

void check(int x, int y, int turn, vector<int> &can, int mask) {
    if(turn == 11) return;
    const static int dx[] = {1, 0, -1, 0};
    const static int dy[] = {0, 1, 0, -1};
    for(int i = 0; i < 4; ++i) {
        const int nx = x + dx[i]*turn;
        const int ny = y + dy[i]*turn;
        if(nx == 0 && ny == 0) {
            can[turn] |= mask;
        }
        check(nx, ny, turn+1, can, mask);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N;
    vector<int> can(11, 0);
    cin >> N;
    for(int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        check(x, y, 1, can, (1<<i));
    }
    int ans = -1;
    for(int i = 0; i <= 10; ++i) {
        if(can[i] == (1<<N)-1) {
            ans = i;
            break;
        }
    }
    cout << ans << endl;
    return 0;
}
