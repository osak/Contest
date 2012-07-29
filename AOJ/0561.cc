//Name: Books
//Level: 3
//Category: DP,動的計画法
//Note:

/*
 * 同じジャンルの中では，高いものから順に売っていくのが最適なことは自明．
 * あとはジャンルごとに何冊ずつ売るかを決めればよいのだが，これは
 * ・ジャンルgまでを使ってn冊の本を売る
 * ときの売値の最大値を考えると
 * ・ジャンルg-1までを使ってn-k冊の本を売るときの最大値に加え，ジャンルgでk冊の本を売る
 * の(kについての)最大値であることが分かる(ジャンルgでの選択はジャンルg-1まででの選択に影響しないため)．
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

inline bool update(int &a, int v) {
    if(a > v) return false;
    a = v;
    return true;
}

// dp[using_upto_g][sale_books]
int dp[10][2001];
int main() {
    int N, K;
    cin >> N >> K;
    vector<vector<int> > books_of(10);
    for(int i = 0; i < N; ++i) {
        int c, g;
        cin >> c >> g;
        --g;
        books_of[g].push_back(c);
    }
    vector<vector<int> > values_of(10);
    for(int i = 0; i < 10; ++i) {
        vector<int> &books = books_of[i];
        vector<int> &values = values_of[i];
        values.push_back(0);
        sort(books.begin(), books.end());
        reverse(books.begin(), books.end());
        const int BN = books.size();
        int acc = 0;
        for(int j = 0; j < BN; ++j) {
            acc += books[j];
            int v = acc;
            if(j > 0) v += j*(j+1);
            values.push_back(v);
        }
    }
    for(int sale = 0; sale < (int)values_of[0].size(); ++sale) {
        dp[0][sale] = values_of[0][sale];
    }
    for(int g = 1; g < 10; ++g) {
        const vector<int> &values = values_of[g];
        const int VN = (int)values.size();
        for(int sale = 0; sale <= K; ++sale) {
            update(dp[g][sale], dp[g-1][sale]);
            for(int prev = 0; prev < sale; ++prev) {
                if(sale-prev < VN) update(dp[g][sale], dp[g-1][prev] + values[sale-prev]);
            }
        }
    }
    cout << dp[9][K] << endl;
    return 0;
}
