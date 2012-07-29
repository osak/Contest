#include <iostream>
#include <vector>

using namespace std;

int main() {
    while(true) {
        int n;
        cin >> n;
        if(!n) break;
        vector<int> cards(2*n+1, 1);
        vector<int> rem(2, n);
        for(int i = 0; i < n; ++i) {
            int c;
            cin >> c;
            cards[c] = 0;
        }

        int field = 0;
        int turn = 0;
        while(true) {
            bool played = false;
            for(int i = field+1; i <= 2*n; ++i) {
                if(cards[i] == turn) {
                    if(--rem[turn] == 0) goto end;
                    cards[i] = -1;
                    turn = 1-turn;
                    field = i;
                    played = true;
                    break;
                }
            }
            if(!played) {
                field = 0;
                turn = 1-turn;
            }
        }
end:
        cout << rem[1] << endl;
        cout << rem[0] << endl;
    }
    return 0;
}
