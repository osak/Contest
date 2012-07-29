#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int modecnt = 0;
    map<int, int> m;
    int n;
    while(cin >> n) 
        modecnt = max(modecnt, ++m[n]);

    vector<int> ans;
    for(map<int,int>::iterator it = m.begin(); it != m.end(); ++it)
        if(it->second == modecnt) ans.push_back(it->first);
    sort(ans.begin(), ans.end());
    for(int i = 0; i < ans.size(); ++i)
        cout << ans[i] << endl;

    return 0;
}
