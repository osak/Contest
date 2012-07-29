#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
    set<string> enemy_used;
    char prev = 'a';

    for(int i = 0; i < 50; ++i) {
        string s = "?";
        s += prev;
        s += 'a'+i/26;
        s += 'a'+i%26;
        s += 'a';
        cout << s << endl;
        cout.flush();

        string ans;
        cin >> ans;
        if(ans[0] != 'a' || enemy_used.count(ans)) {
            cout << "!OUT" << endl;
            cout.flush();
            break;
        }

        enemy_used.insert(ans);
        prev = ans[ans.size()-1];
    }

    return 0;
}
