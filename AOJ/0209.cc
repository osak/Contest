#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

void printmtx(const vector<vector<int> > &v) {
    for(int y = 0; y < v.size(); ++y) {
        for(int x = 0; x < v[y].size(); ++x)
            printf("%3d", v[y][x]);
        printf("\n");
    }
    puts("");
}


int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<vector<int> > photo(N, vector<int>(N, -1));
        vector<vector<vector<int> > > piece(4, vector<vector<int> >(M, vector<int>(M, -1)));

        for(int y = 0; y < N; ++y)
            for(int x = 0; x < N; ++x)
                cin >> photo[y][x];

        for(int y = 0; y < M; ++y)
            for(int x = 0; x < M; ++x)
                cin >> piece[0][y][x];

        for(int m = 1; m < 4; ++m) {
            for(int y = 0; y < M; ++y)
                for(int x = 0; x < M; ++x)
                    piece[m][x][M-y-1] = piece[m-1][y][x];
        }

        int ax = -1, ay = -1;
        for(int y = 0; y <= N-M; ++y) {
            for(int x = 0; x <= N-M; ++x) {
                for(int m = 0; m < 4; ++m) {
                    for(int py = 0; py < M; ++py) {
                        for(int px = 0; px < M; ++px) {
                            if(piece[m][py][px] == -1) continue;
                            if(piece[m][py][px] != photo[y+py][x+px]) {
                                goto nextpos;
                            }
                        }
                    }
                    for(int py = 0; py < M; ++py) {
                        for(int px = 0; px < M; ++px) {
                            if(piece[m][py][px] != -1) {
                                ax = px+x+1;
                                ay = py+y+1;
                                goto endloop;
                            }
                        }
                    }
nextpos:
                    ;
                }
            }
        }
endloop:
        if(ax != -1) cout << ax << ' ' << ay << endl;
        else cout << "NA" << endl;
    }
    return 0;
}
