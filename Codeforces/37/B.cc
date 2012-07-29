#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<int, int> Scroll;

int main() {
    int N, M, R;
    cin >> N >> M >> R;

    vector<Scroll> scrolls(N);
    vector<bool> used(N, false);
    for(int i = 0; i < N; ++i) {
        int p, d;
        cin >> p >> d;
        scrolls[i].first = M*p/100;
        scrolls[i].second = d;
    }

    bool ok = true;
    int hp = M;
    int turn = 0;
    int dmg = 0;
    int pos = 0;
    vector<pair<int, int> > history;
    while(true) {
        int d = dmg - R;
        hp = min(hp-d, M);
        if(hp <= 0) break;

        int cast_spell = -1;
        int cast_spell_dmg = -1;
        for(int i = 0; i < N; ++i) {
            if(used[i]) continue;
            if(hp <= scrolls[i].first && scrolls[i].second > cast_spell_dmg) {
                cast_spell = i;
                cast_spell_dmg = scrolls[i].second;
            }
        }
        if(cast_spell != -1) {
            used[cast_spell] = true;
            dmg += cast_spell_dmg;
            history.push_back(make_pair(turn, cast_spell+1));
        }
        else if(d <= 0) {
            ok = false;
            break;
        }
        ++turn;
    }
    if(ok) {
        cout << "YES" << endl;
        cout << turn << " " << history.size() << endl;
        for(int i = 0; i < history.size(); ++i) {
            cout << history[i].first << " " << history[i].second << endl;
        }
    }
    else {
        cout << "NO" << endl;
    }
    return 0;
}
