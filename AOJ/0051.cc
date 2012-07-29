//Name: Differential II
//Level: 1
//Category: ソート,やるだけ
//Note:

#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    while(N--) {
        string str;
        cin >> str;
        sort(str.begin(), str.end());
        int min = atoi(str.c_str());
        reverse(str.begin(), str.end());
        int max = atoi(str.c_str());
        cout << max-min << endl;
    }
    return 0;
}
