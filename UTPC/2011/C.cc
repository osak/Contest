#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    string str;
    cin >> str;

    map<char, char> m;
    m['i'] = 'i';
    m['w'] = 'w';
    m['('] = ')';
    m[')'] = '(';
    m['{'] = '}';
    m['}'] = '{';
    m['['] = ']';
    m[']'] = '[';

    int sep = str.find("i");
    string pre = str.substr(0, sep);
    string post = str.substr(sep+3);
    reverse(post.begin(), post.end());

    vector<vector<int> > dp(pre.size()+1, vector<int>(post.size()+1, 0));
    for(int i = 0; i < pre.size(); ++i) {
        for(int j = 0; j < post.size(); ++j) {
            dp[i+1][j+1] = max(dp[i+1][j], dp[i][j+1]);
            if(m[pre[i]]==post[j]) dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]+2);
        }
    }
    cout << dp[pre.size()][post.size()]+3 << endl;
}
