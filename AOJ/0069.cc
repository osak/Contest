//Name: Drawing Lots II
//Level: 2
//Category: シミュレーション,数学
//Note:

/*
 * あみだくじは隣どうし交換するだけなので，初期状態で当たりに到達する場所targetをまず調べ，
 * その後で自分の選んだ箇所とtargetが隣り合うときに横棒を加え，交換すればよい．
 * 横棒が二重に置けないことと，横棒が連続してはいけないことに注意．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;
        int M, G, D;
        cin >> M >> G >> D;
        vector<string> lots(D);
        for(int i = 0; i < D; ++i) {
            cin >> lots[i];
            lots[i] = '0' + lots[i] + '0';
        }
        vector<vector<int> > history(D+1, vector<int>(N+2));
        for(int i = 0; i <= N+1; ++i) history[0][i] = i;

        //Simulation
        for(int turn = 1; turn < D+1; ++turn) {
            history[turn] = history[turn-1];
            for(int i = 1; i < N; ++i)
                if(lots[turn-1][i] == '1') swap(history[turn][i], history[turn][i+1]);
        }
        int target = history[D][G];
        if(target == M) cout << 0 << endl;
        else {
            for(int turn = 0; turn < D; ++turn) {
                for(int i = 1; i <= N; ++i) {
                    if(history[turn][i] == M) {
                        if(history[turn][i-1] == target && lots[turn].substr(i-2,3) == "000") {
                            cout << turn+1 << ' ' << i-1 << endl;
                            goto next;
                        }
                        else if(history[turn][i+1] == target && lots[turn].substr(i-1,3) == "000") {
                            cout << turn+1 << ' ' << i << endl;
                            goto next;
                        }
                    }
                }
            }
            cout << 1 << endl;
        }
next:
        ;
    }
    return 0;
}
