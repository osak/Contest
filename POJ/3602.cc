//Name: Typographical Ligatures
//Level: 1
//Category: 文字列,やるだけ
//Note:

/**
 * 長いリガチャから順に調べていけばよい。
 *
 * オーダーはO(NPS)。
 * ただし、Nは文字列長、Pはパターン数、Sは最も長いパターン長。
 * この問題ではP=7, S=3である。
 */
#include <iostream>
#include <string>
#include <map>

using namespace std;

const string ligature_f[] = {
    "ffi", "ffl", "ff", "fi", "fl", ""
};

const string ligature_oq[] = {"``", ""};
const string ligature_cq[] = {"''", ""};

int main() {
    string str;
    map<string,bool> glyph;
    while(cin >> str) {
        const int N = str.size();
        for(int i = 0; i < N; ) {
            const string *ligatures = NULL;
            if(str[i] == 'f') {
                ligatures = ligature_f;
            } else if(str[i] == '`') {
                ligatures = ligature_oq;
            } else if(str[i] == '\'') {
                ligatures = ligature_cq;
            }
            if(ligatures) {
                const string *lp = ligatures;
                while(*lp != "") {
                    if(str.substr(i, lp->size()) == *lp) {
                        glyph[*lp] = true;
                        i += lp->size();
                        goto next;
                    }
                    ++lp;
                }
            }
            if(str[i] != ' ') {
                glyph[str.substr(i, 1)] = true;
                ++i;
            }
next:
            ;
        }
    }
    printf("%d\n", glyph.size());
    return 0;
}
