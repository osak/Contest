#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

vector<vector<int> > adj(20);
map<string, int> memo;

int dfs(const string &str) {
    map<string, int>::iterator it;
    if(str.size() <= 1) return str.size();
    if((it = memo.find(str)) != memo.end()) return it->second;

    int ans = str.size();
    for(int i = 0; i < str.size(); ++i) {
        for(int j = 0; j < adj[i].size(); ++j) {
            if(adj[i][j] >= str.size()) continue;
            if(adj[i][j] < i) continue;
            if(str[i] == str[adj[i][j]]) {
                ans = min(ans, dfs(str.substr(0, i) + str.substr(i+1, adj[i][j]-(i+1)) + str.substr(adj[i][j]+1)));
            }
        }
    }

    memo[str] = ans;
    return ans;
}


int main() {
    for(int i = 0; i < 20; ++i) {
        int x = i % 4;
        int y = i / 4;

        for(int dx = -1; dx <= 1; ++dx) {
            for(int dy = -1; dy <= 1; ++dy) {
                if(dx == 0 && dy == 0) continue;
                int xx = x + dx, yy = y + dy;
                if(0 <= xx && xx < 4 && 0 <= yy && yy < 5) {
                    adj[i].push_back(yy*4 + xx);
                }
            }
        }
    }

    int N;
    cin >> N;
    while(N--) {
        string s;
        for(int i = 0; i < 20; ++i) {
            char c;
            cin >> c;
            s += c;
        }

        cout << dfs(s) << endl;
    }
    return 0;
}
