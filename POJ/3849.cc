//Name: Settlers of Catan
//Level: 3
//Category: Hex,HoneyComb,シミュレーション
//Note:

/*
 * シミュレーションするだけ．
 * ハニカムは斜交座標を取ると遷移行列を書きやすい．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int field[200][200];
const int DX[] = {1, 1, 0, -1, -1, 0};
const int DY[] = {0, -1, -1, 0, 1, 1, 0};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<int> freq(6, 0);
    vector<int> nums;
    int x = 100, y = 100;
    field[x][y] = 1;
    nums.push_back(1);
    freq[1]++;
    x += DX[0]; y += DY[0];
    field[x][y] = 2;
    nums.push_back(2);
    freq[2]++;
    int prevdir = 2;
    for(int TIMES = 3; TIMES <= 10000; ++TIMES) {
        //cout << x << ' ' << y << endl;
        for(int dd = 0; dd < 6; ++dd) {
            const int dir = (prevdir+dd) % 6;
            const int nx = x + DX[dir];
            const int ny = y + DY[dir];
            if(field[nx][ny] != 0) continue;

            int cnt = 0;
            for(int neigh = 0; neigh < 6; ++neigh) {
                const int nnx = nx + DX[neigh];
                const int nny = ny + DY[neigh];
                if(field[nnx][nny] != 0) ++cnt;
            }
            if(cnt >= 2) {
                //cout << dir << endl;
                x = nx;
                y = ny;
                prevdir = dir;
                break;
            }
        }
        vector<int> can(6, 1);
        for(int dir = 0; dir < 6; ++dir) {
            const int nx = x + DX[dir];
            const int ny = y + DY[dir];
            if(field[nx][ny] != 0) can[field[nx][ny]] = 0;
        }
        int num = -1;
        int minval = 10000;
        for(int i = 1; i <= 5; ++i) {
            if(can[i]) {
                if(freq[i] < minval) {
                    num = i;
                    minval = freq[i];
                }
            }
        }
        nums.push_back(num);
        field[x][y] = num;
        freq[num]++;
    }
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        cout << nums[n-1] << endl;
    }
    return 0;
}
