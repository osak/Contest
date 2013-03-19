#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <set>

using namespace std;

// Suffix Array {{{
struct SAComp {
    const vector<int> *grp;
    int h;
    SAComp(const vector<int> *grp, int h) : grp(grp), h(h) {}

    bool operator ()(int a, int b) const {
        int va = grp->at(a);
        int vb = grp->at(b);
        int vah = a+h < grp->size() ? grp->at(a+h) : INT_MIN;
        int vbh = b+h < grp->size() ? grp->at(b+h) : INT_MIN;
        return (va == vb) ? vah < vbh : va < vb;
    }
};

// Suffix Arrayを構築する．
// A Fast Algorithm for Making Suffix Arrays and for Burrows-Wheeler Transformation
// (Kunihiko Sadakane, 1998)
// の実装．ただし，以下の変更を加えている．
// ・同じグループごとにソートするのではなく，Suffix Array全体を一度にソートする．
// saの中身は開始インデックス．
//
// 計算量O(N (log N)^2)
void suffix_array(const string &str, vector<int> &sa) {
    assert(sa.size() >= str.size());

    int N = str.size();
    vector<int> group(N, 0), next(N, 0);
    for(int i = 0; i < N; ++i) {
        sa[i] = i;
        group[i] = str[i];
    }
    {
        SAComp cmp(&group, 0);
        sort(sa.begin(), sa.end(), cmp);
        next[sa[0]] = 0;
        for(int i = 1; i < N; ++i) {
            next[sa[i]] = next[sa[i-1]] + cmp(sa[i-1], sa[i]);
        }
        group.swap(next);
    }

    for(int h = 1; h < N && group[N-1] != N-1; h <<= 1) {
        //Generate <_{2*h} ordered array from <_{h} ordered array
        //この中身はcmpのコンストラクタ引数以外，上のブロックと同じ．
        SAComp cmp(&group, h);
        sort(sa.begin(), sa.end(), cmp);
        next[sa[0]] = 0;
        for(int i = 1; i < N; ++i) {
            next[sa[i]] = next[sa[i-1]] + cmp(sa[i-1], sa[i]);
        }
        group.swap(next);
    }
}

// 文字列を検索する．
// 複数の候補がある場合，最初に一致したインデックスを返す．
// 計算量O(M log N)
int find(const string &src, const string &str, const vector<int> &sa) {
    int left = 0, right = sa.size();
    while(left < right) {
        int mid = (left+right)/2;
        int res = src.compare(sa[mid], min(src.size()-sa[mid], str.size()), str);
        if(res == 0) return mid;
        if(res < 0) left = mid+1;
        else right = mid;
    }
    return -1;
}/*}}}*/

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    string s;
    getline(cin, s);
    vector<int> sa(s.size());
    suffix_array(s, sa);
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i) {
        string query;
        cin >> query;
        set<string> seen;
