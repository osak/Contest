#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    char arr[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    string line;
    cin >> line;
    const int N = line.size();

    bool ok = true;
    do {
        ok = true;
        set<char> used;
        int arrpos = 7;
        for(int i = 0; i < 8; ++i) {
            const int pos = N-i-1;
            if(!used.count(line[pos]) && arr[arrpos] != line[pos]) {
                ok = false;
                break;
            }
            used.insert(arr[arrpos--]);
        }
        if(ok) break;
    } while(next_permutation(arr, arr+8));
    cout << string(arr, 8) << endl;
    return 0;
}
