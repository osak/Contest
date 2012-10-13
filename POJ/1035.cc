//Name: Spell checker
//Level: 2
//Category: 文字列
//Note:

/*
 * 辞書の各単語について，入力の単語の1文字削除，1文字置換，1文字挿入でその単語にできるかを確かめればよい．
 * また，辞書の単語と入力の単語の長さで枝刈りが可能．
 *
 * オーダーは辞書の語数を N ，入力の語数を M ，最大文字列長を L として O(NML)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool deleting(const string &src, const string &dst) {
    if((int)src.size()-1 != (int)dst.size()) return false;
    const int N = (int)src.size();
    bool deleted = false;
    for(int i = 0; i < N; ++i) {
        const int dst_pos = deleted ? i-1 : i;
        if(src[i] != dst[dst_pos]) {
            if(deleted) return false;
            deleted = true;
        }
    }
    return true;
}

bool replacing(const string &src, const string &dst) {
    if(src.size() != dst.size()) return false;
    const int N = (int)src.size();
    bool replaced = false;
    for(int i = 0; i < N; ++i) {
        if(src[i] != dst[i]) {
            if(replaced) return false;
            replaced = true;
        }
    }
    return true;
}

bool inserting(const string &src, const string &dst) {
    if(src.size()+1 != dst.size()) return false;
    const int N = (int)dst.size();
    bool inserted = false;
    for(int i = 0; i < N; ++i) {
        const int src_pos = inserted ? i-1 : i;
        if(src[src_pos] != dst[i]) {
            if(inserted) return false;
            inserted = true;
        }
    }
    return true;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<string> dict;
    while(true) {
        string word;
        cin >> word;
        if(word == "#") break;
        dict.push_back(word);
    }
    while(true) {
        string word;
        cin >> word;
        if(word == "#") break;
        string res = word + ":";
        for(vector<string>::iterator it = dict.begin(); it != dict.end(); ++it) {
            if(word == *it) {
                res = word + " is correct";
                break;
            }
            if(deleting(word, *it) || replacing(word, *it) || inserting(word, *it)) res += " " + *it;
        }
        cout << res << endl;
    }
    return 0;
}
