//Name: Poker Hand 
//Level: 1
//Category: シミュレーション,場合分け
//Note:

/*
 * 変にループ等を使うよりは、全ての手をハードコーディングしたほうが楽。
 */

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    string line;
    while(cin >> line) {
        for(int i = 0; i < line.size(); ++i)
            if(line[i] == ',') line[i] = ' ';
        istringstream is(line);
        int v[5];
        for(int i = 0; i < 5; ++i) is >> v[i];

        sort(v, v+5);
        string ans;
        if(v[1]==v[2] && v[2]==v[3] && (v[0]==v[1]||v[3]==v[4])) ans = "four card";
        else if((v[0]==v[1] && (v[2]==v[3] && v[3]==v[4])) || ((v[0]==v[1] && v[1]==v[2]) && v[3]==v[4])) ans = "full house";
        else if(v[0]+1==v[1] && v[1]+1==v[2] && v[2]+1==v[3] && v[3]+1==v[4]) ans = "straight";
        else if(v[0]==1 && v[1]==10 && v[2]==11 && v[3]==12 && v[4]==13) ans = "straight";
        else if((v[0]==v[1] && v[1]==v[2]) || (v[1]==v[2] && v[2]==v[3]) || (v[2]==v[3] && v[3]==v[4])) ans = "three card";
        else if(unique(v, v+5) - v == 3) ans = "two pair";
        else if(unique(v, v+5) - v == 4) ans = "one pair";
        else ans = "null";

        cout << ans << endl;
    }
    return 0;
}
