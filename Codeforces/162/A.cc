//Name: Escape from Stones
//Level: 2
//Category: シミュレーション
//Note:

/**
 * 連結リストを使ってシミュレーションする。
 *
 * オーダーは O(N)。
 */
#include <iostream>
#include <list>
#include <string>

using namespace std;

struct Tag {
    int label;
    Tag *next;
    Tag() : label(0), next(nullptr) {}
} tags[1000001];

bool solve() {
    string str;
    if(!(cin >> str)) return false;
    const int N = str.size();
    Tag *top = &tags[N];
    top->next = nullptr;
    Tag *cur = top;
    for(int i = 0; i < N; ++i) {
        Tag *t = &tags[i];
        t->label = i+1;
        t->next = cur->next;
        cur->next = t;
        if(str[i] == 'r') {
            cur = t;
        }
    }
    cur = top->next;
    while(cur) {
        cout << cur->label << endl;
        cur = cur->next;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
