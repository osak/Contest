#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<string> > words(1001);
vector<int> needcnt(1001, 0);
int allcnt;

bool dfs(const string &prefix) {
    int len = prefix.size()+1;
    if(needcnt[len]) {
        words[len].push_back(prefix + "0");
        needcnt[len]--;
        if(--allcnt == 0) return true;
        if(needcnt[len]) {
            words[len].push_back(prefix + "1");
            needcnt[len]--;
            if(--allcnt == 0) return true;
            else return false;
        }
        else {
            return dfs(prefix + "1");
        }
    }
    else {
        if(dfs(prefix + "0")) return true;
        if(dfs(prefix + "1")) return true;
    }
    return false;
}

int main() {
    cin >> allcnt;
    vector<int> order(allcnt);
    for(int i = 0; i < allcnt; ++i) {
        cin >> order[i];
        needcnt[order[i]]++;
    }
    if(dfs("")) {
        cout << "YES" << endl;
        for(int i = 0; i < order.size(); ++i) {
            int o = order[i];
            cout << words[o].back() << endl;
            words[o].pop_back();
        }
    }
    else {
        cout << "NO" << endl;
    }
    return 0;
}
