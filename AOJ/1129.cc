#include <iostream>
#include <vector>

using namespace std;

int main() {
    while(true) {
        int N, R;
        cin >> N >> R;
        if(!N && !R) break;

        vector<int> cards(N);
        for(int i = 0; i < N; ++i) cards[i] = N-i;

        while(R--) {
            int P, C;
            cin >> P >> C;
            P--;
            vector<int> tmp;
            for(int i = 0; i < C; ++i) tmp.push_back(cards[P+i]);
            for(int i = 0; i < P; ++i) tmp.push_back(cards[i]);
            for(int i = P+C; i < N; ++i) tmp.push_back(cards[i]);
            cards = tmp;
        }

        cout << cards[0] << endl;
    }
    return 0;
}
