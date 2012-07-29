#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;

string replace(const string &s, const string &a, const string &b) {
    int prev = 0, pos = 0;
    string res = "";
    while((pos = s.find(a, prev)) != string::npos) {
        res += s.substr(prev, pos-prev);
        res += b;
        prev = pos+a.size();
    }
    res += s.substr(prev);
    return res;
}

int dfs(const string &s, const string &g, const vector<pair<string,string> > &v) {
    if(s == g) return 0;
    if(s.size() >= g.size()) return 100;

    int ans = 100;
    for(int i = 0; i < v.size(); ++i) {
        string next = replace(s, v[i].first, v[i].second);
        if(next == s) continue;
        ans = min(ans, dfs(next, g, v)+1);
    }

    return ans;
}

int main() {
    assert(replace("a", "a", "bb") == "bb");
    assert(replace("aa", "a", "bb") == "bbbb");

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<pair<string,string> > v;
        for(int i = 0; i < N; ++i) {
            string a, b;
            cin >> a >> b;
            v.push_back(make_pair(a, b));
        }
        
        string s, g;
        cin >> s >> g;
        int ans = dfs(s, g, v);
        cout << (ans==100?-1:ans) << endl;
    }

    return 0;
}
