//Name: Sum of Cards
//Level: 2
//Category: 再帰,数え上げ
//Note:

/*
 * 使うカードの組み合わせは高々10^7通りなので，DFSで全パターン列挙できる．
 */
#include <iostream>
#include <vector>

using namespace std;

void dfs(int pos, int acc, int lim, const vector<pair<int,int> > &cards, vector<int> &patterns) {
    const int N = cards.size();
    if(acc > lim) return;
    if(pos == N) {
        patterns[acc]++;
        return;
    }
    for(int i = 0; i <= cards[pos].second; ++i) {
        dfs(pos+1, acc+cards[pos].first*i, lim, cards, patterns);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N;
        cin >> N;
        if(!N) break;
        vector<pair<int,int> > cards(N);
        for(int i = 0; i < N; ++i) {
            cin >> cards[i].first >> cards[i].second;
        }
        vector<int> patterns(1001, 0);
        dfs(0, 0, 1000, cards, patterns);

        int G;
        cin >> G;
        while(G--) {
            int NG;
            cin >> NG;
            cout << patterns[NG] << endl;
        }
    }
    return 0;
}
