//Name: Railway Lines
//Level: 2
//Category: シミュレーション,境界条件
//Note:

/*
 * すれ違う点は計算で出る。
 * ちょうど駅のところですれ違うときの処理に注意。
 */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    string line;
    while(cin >> line) {
        for(int i = 0; i < line.size(); ++i) 
            if(line[i] == ',') line[i] = ' ';
        istringstream is(line);
        vector<int> ls(10);
        int v1, v2;
        for(int i = 0; i < 10; ++i) is >> ls[i];
        is >> v1 >> v2;
        int len = accumulate(ls.begin(), ls.end(), 0);
        int pos = v1*len/(v1+v2);
        int mod = v1*len%(v1+v2);
        int acc = 0;
        for(int i = 0; i < 10; ++i) {
            acc += ls[i];
            if(acc >= pos) {
                if(acc > pos || (acc == pos && mod == 0)) cout << i+1 << endl;
                else cout << i+2 << endl;
                break;
            }
        }
    }
    return 0;
}
