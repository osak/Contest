//Name: Shuffle The Cards
//Level: 2
//Category: シミュレーション
//Note:

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> cards;
    for(int i = 1; i <= 2*n; ++i) {
        cards.push_back(i);
    }

    while(m--) {
        int k;
        cin >> k;
        if(k == 0) {
            vector<int> upper(cards.begin(), cards.begin()+n);
            vector<int> lower(cards.begin()+n, cards.end());
            for(int i = 0; i < n; ++i) {
                cards[i*2] = upper[i];
                cards[i*2+1] = lower[i];
            }
        }
        else {
            vector<int> upper(cards.begin(), cards.begin()+k);
            vector<int> lower(cards.begin()+k, cards.end());
            copy(upper.begin(), upper.end(), copy(lower.begin(), lower.end(), cards.begin()));
        }
    }
    for(int i = 0; i < cards.size(); ++i) {
        cout << cards[i] << endl;
    }
    return 0;
}
