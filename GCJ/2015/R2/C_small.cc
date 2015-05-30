//Name: 
//Level: 
//Category: 
//Note: 

/**
 *
 */
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <bitset>

using namespace std;

typedef bitset<2000> WordVec;

unordered_map<string,int> dict;

WordVec tokens() {
    string line;
    WordVec res;
    getline(cin, line);
    istringstream is(line);
    while(!is.eof()) {
        string token;
        is >> token;
        if(!dict.count(token)) {
            const int idx = dict.size();
            dict[token] = idx;
        }
        res[dict[token]] = 1;
    }
    return res;
}

int solve() {
    dict.clear();

    int N;
    cin >> N;
    cin.ignore();

    WordVec english_base = tokens();
    WordVec french_base = tokens();
    vector<WordVec> words;
    for(int i = 0; i < N-2; ++i) {
        words.push_back(tokens());
    }

    int ans = 2000 * N;
    for(int pat = 0; pat < (1<<(N-2)); ++pat) {
        WordVec en = english_base, fr = french_base;
        for(int i = 0; i < N-2; ++i) {
            if(pat & (1<<i)) {
                en |= words[i];
            } else {
                fr |= words[i];
            }
        }
        ans = min(ans, (int)(en & fr).count());
    }
    return ans;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    int T;
    cin >> T;
    for(int i = 1; i <= T; ++i) {
        cout << "Case #" << i << ": " << solve() << endl;
    }
    return 0;
}
