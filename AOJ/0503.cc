//Name: Cup
//Level: 4
//Category: シミュレーション,数論
//Note:

/*
 * Aに積まれたN個のカップをCに移すときの手順は
 * ・AのN-1個のカップをCに移す
 * ・Aに残ったカップをBに移す
 * ・CのN-1個のカップをAに移す
 * ・Bに残っているカップをCに移す
 * ・AのN-1個のカップをCに移す
 * となるから，3^N-1手かかる．
 * それぞれのカップはトレイA-Cのどこにでも置けるから，可能な状態数は3^N．
 * したがって，普通に解けば全状態を網羅することになるので，当然初期状態もこの中に含まれる．
 * あとは解く手順をシミュレーションしながら初期状態が出現した手数を覚えておき，逆順に動かしたときも考えて小さいほうを手数として採用すればよい．
 */
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int pow_(int a, int x) {
    int val = 1;
    for(int i = 0; i < x; ++i) val *= a;
    return val;
}

int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<vector<int> > goal(3);
        for(int i = 0; i < 3; ++i) {
            int n;
            cin >> n;
            while(n--) {
                int idx;
                cin >> idx;
                goal[i].push_back(idx-1);
            }
        }

        vector<vector<int> > field(3);
        for(int i = 0; i < N; ++i) {
            field[0].push_back(i);
        }

        int turn = 0;
        int prev_from = -1;
        int prev_to = -1;
        while(true) {
            if(field == goal) {
                break;
            }
            ++turn;
            for(int from = 0; from < 3; ++from) {
                if(field[from].size() == 0) continue;
                const int glass = field[from].back();
                const int to_1 = from-1;
                const int to_2 = from+1;
                if(!(from == prev_to && to_1 == prev_from) && to_1 >= 0 && (field[to_1].size() == 0 || field[to_1].back() < glass)) {
                    field[to_1].push_back(glass);
                    field[from].pop_back();
                    prev_from = from;
                    prev_to = to_1;
                    break;
                }
                else if(!(from == prev_to && to_2 == prev_from) && to_2 < 3 && (field[to_2].size() == 0 || field[to_2].back() < glass)) {
                    field[to_2].push_back(glass);
                    field[from].pop_back();
                    prev_from = from;
                    prev_to = to_2;
                    break;
                }
                else {
                }
            }
        }
        const int MAXTURN = pow_(3, N) - 1;
        turn = min(turn, MAXTURN-turn);
        if(turn > M) turn = -1;
        cout << turn << endl;
    }
    return 0;
}
