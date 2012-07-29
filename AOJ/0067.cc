//Name: The Number of Island
//Level: 1
//Category: 塗り潰し,やるだけ
//Note:

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int d[][2] = { {0,1}, {-1,0}, {0,-1}, {1,0} };

void fill(vector<string> &v, int r, int c) {
    int R = v.size();
    int C = v[0].size();

    if(r < 0 || R <= r || c < 0 || C <= c) return;
    if(v[r][c] != '1') return;
    v[r][c] = '0';

    for(int i = 0; i < 4; ++i) {
        int nr = r + d[i][0];
        int nc = c + d[i][1];
        fill(v, nr, nc);
    }
}


int main() {
    while(true) {
        vector<string> v(12);
        for(int i = 0; i < 12; ++i) cin >> v[i];
        if(cin.eof()) break;

        int ans = 0;
        for(int r = 0; r < 12; ++r)
            for(int c = 0; c < 12; ++c)
                if(v[r][c] == '1') {
                    fill(v, r, c);
                    ++ans;
                }
        cout << ans << endl;
    }
    return 0;
}
