//Name: Dice
//Level: 2
//Category: シミュレーション
//Note:

#include <iostream>
#include <string>

using namespace std;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        int dice[] = {1,3,6,4,2,5};
        int sum = 1;
        while(N--) {
            string cmd;
            cin >> cmd;
            if(cmd == "North") {
                int tmp = dice[0];
                dice[0] = dice[4];
                dice[4] = dice[2];
                dice[2] = dice[5];
                dice[5] = tmp;
            }
            else if(cmd == "East") {
                int tmp = dice[0];
                dice[0] = dice[3];
                dice[3] = dice[2];
                dice[2] = dice[1];
                dice[1] = tmp;
            }
            else if(cmd == "South") {
                int tmp = dice[0];
                dice[0] = dice[5];
                dice[5] = dice[2];
                dice[2] = dice[4];
                dice[4] = tmp;
            }
            else if(cmd == "West") {
                int tmp = dice[0];
                dice[0] = dice[1];
                dice[1] = dice[2];
                dice[2] = dice[3];
                dice[3] = tmp;
            }
            else if(cmd == "Right") {
                int tmp = dice[4];
                dice[4] = dice[1];
                dice[1] = dice[5];
                dice[5] = dice[3];
                dice[3] = tmp;
            }
            else if(cmd == "Left") {
                int tmp = dice[4];
                dice[4] = dice[3];
                dice[3] = dice[5];
                dice[5] = dice[1];
                dice[1] = tmp;
            }
            sum += dice[0];
        }
        cout << sum << endl;
    }
    return 0;
}
