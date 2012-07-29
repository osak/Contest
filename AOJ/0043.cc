//Name: Puzzle
//Level: 2
//Category: シミュレーション,深さ優先探索,全探索
//Note:

/*
 * 麻雀の待ち判定。
 * それぞれの牌を加えてみて、役になるか判定すればよい。
 * 判定は雀頭を最初に取って、次に4回順子、刻子の取りかたを全探索する。
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool rec(vector<int> &v, int level) {
    if(level == 5) return true;
    //雀頭
    if(level == 0) {
        for(int i = 0; i < v.size(); ++i) {
            if(v[i] >= 2) {
                v[i] -= 2;
                if(rec(v, level+1)) return true;
                v[i] += 2;
            }
        }
    }
    else {
        //順子
        for(int i = 0; i < v.size()-2; ++i) {
            if(v[i] >= 1 && v[i+1] >= 1 && v[i+2] >= 1) {
                v[i]--; v[i+1]--; v[i+2]--;
                if(rec(v, level+1)) return true;
                v[i]++; v[i+1]++; v[i+2]++;
            }
        }
        //刻子
        for(int i = 0; i < v.size(); ++i) {
            if(v[i] >= 3) {
                v[i] -= 3;
                if(rec(v, level+1)) return true;
                v[i] += 3;
            }
        }
    }
    return false;
}

bool check(const vector<int> &v) {
    vector<int> tmp = v;
    return rec(tmp, 0);
}


int main() {
    string line;
    while(cin >> line) {
        vector<int> cnt(9, 0);
        for(int i = 0; i < line.size(); ++i)
            cnt[line[i]-'1']++;
        vector<int> v;
        for(int i = 1; i <= 9; ++i) {
            if(cnt[i-1] == 4) continue;
            cnt[i-1]++;
            if(check(cnt)) v.push_back(i);
            cnt[i-1]--;
        }
        if(v.size() == 0) v.push_back(0);
        for(int i = 0; i < v.size(); ++i) {
            if(i > 0) cout << ' ';
            cout << v[i];
        }
        cout << endl;
    }
    return 0;
}
