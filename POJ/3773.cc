//Name: String-Matching Automata
//Level: 4
//Category: 文字列,オートマトン
//Note:

/*
 * ノード N の遷移はそれより後のノードには依存しないから，先頭から順に遷移を決めていくことができる．
 * また，あるノードで失敗したときに戻る場所は，そのノードまでの文字列の suffix のうち，
 * 受理したい文字列の先頭とマッチする，最も長い suffix の長さで決まる．
 * 要するにこれは先頭以外の場所からノード N まで続く文字列が何文字目まで受理されているか，ということに等しいので
 * 1文字遅れでオートマトンをたどっていくポインタ shadow を作り，ノード N で失敗したときは shadow からの遷移を
 * 使うようにすればよい．
 *
 * Sample Input を例にすると
 * ababaca に対して shadow は
 * babaca を受理しようと試みる．
 * このとき shadow に必要なノードは全て遷移が完成しており，かつ shadow のいるノードは
 * ababaca 以外の部分列を最大限受理したときのノードになっている．
 *
 * オーダーは O(N)．
 */ 
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true) {
        string line;
        getline(cin, line);
        if(line == "0") break;
        const int N = line.size();
        vector<vector<int> > automaton(N+1, vector<int>(26, 0));
        int shadow = 0;
        for(int i = 0; i < N+1; ++i) {
            // shadow transient
            for(int ch = 0; ch < 26; ++ch) {
                automaton[i][ch] = automaton[shadow][ch];
            }
            if(i < N) {
                shadow = automaton[shadow][line[i]-'a'];
                automaton[i][line[i]-'a'] = i+1;
            }
        }
        for(int i = 0; i <= N; ++i) {
            cout << i;
            for(int ch = 0; ch < 26; ++ch) {
                cout << ' ' << automaton[i][ch];
            }
            cout << endl;
        }
    }
    return 0;
}
