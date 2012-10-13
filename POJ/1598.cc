//Name: Excuses, Excuses!
//Level: 2
//Category: 文字列,やるだけ
//Note: 上から順に出力すればよい

/*
 * キーワードはアルファベットしか含まず，またアルファベット以外の文字で区切られていれば良いので
 * 最初に全てのアルファベットを小文字に，アルファベット以外の記号を空白に置換すればよい．
 *
 * オーダーは最大の Excuse 長を L として O(EL log K)．
 */
#include <iostream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int K, E;
    int CASE = 1;
    while(cin >> K >> E) {
        set<string> keywords;
        for(int i = 0; i < K; ++i) {
            string kwd;
            cin >> kwd;
            for(string::iterator it = kwd.begin(); it != kwd.end(); ++it) {
                *it = tolower(*it);
            }
            keywords.insert(kwd);
        }
        cin.ignore();
        vector<pair<int,string> > excuses(E, make_pair(0, ""));
        int max_score = 0;
        for(int i = 0; i < E; ++i) {
            string line;
            getline(cin, line);
            excuses[i].second = line;
            for(string::iterator it = line.begin(); it != line.end(); ++it) {
                if(isalpha(*it)) *it = tolower(*it);
                else *it = ' ';
            }
            int score = 0;
            istringstream is(line);
            while(!is.eof()) {
                string word;
                is >> word;
                if(keywords.count(word)) ++score;
            }
            excuses[i].first = score;
            max_score = max(max_score, score);
        }
        cout << "Excuse Set #" << CASE << endl;
        for(int i = 0; i < E; ++i) {
            if(excuses[i].first == max_score) cout << excuses[i].second << endl;
        }
        cout << endl;
        ++CASE;
    }
    return 0;
}
