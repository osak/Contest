//Name: ID
//Level: 2
//Category: 動的計画法,DP
//Note:

/*
 * *でない桁はあらかじめチェックサムが計算できる．
 * *の桁は2倍するかどうかを覚えておき先頭から決めていくと，和は10で割った余りまでしか意味を持たないため
 * O(*の数) の DP にできる．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int memo[8][10];
int calc(int pos, int cur, const vector<int> &as, const vector<int> &is_double) {
    if(pos == (int)is_double.size()) return cur==0;

    int &res = memo[pos][cur];
    if(res < 0) {
        res = 0;
        for(vector<int>::const_iterator it = as.begin(); it != as.end(); ++it) {
            int digit = *it;
            if(is_double[pos]) {
                digit *= 2;
                if(digit >= 10) digit = (digit/10)+(digit%10);
            }
            res += calc(pos+1, (cur+digit)%10, as, is_double);
        }
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N;
    while(cin >> N) {
        string str;
        cin >> str;
        int M;
        cin >> M;
        vector<int> as(M);
        for(int i = 0; i < M; ++i) cin >> as[i];

        vector<int> is_double;
        int checksum = 0;
        for(int i = 0; i < N; ++i) {
            const int pos = (int)str.size()-1-i;
            if(str[pos] == '*') {
                is_double.push_back(i%2);
            } else {
                int digit = str[pos]-'0';
                if(i%2 == 1) {
                    digit *= 2;
                    if(digit >= 10) digit = (digit/10)+(digit%10);
                }
                checksum += digit;
                checksum %= 10;
            }
        }
        fill_n((int*)memo, sizeof(memo)/sizeof(int), -1);
        cout << calc(0, checksum, as, is_double) << endl;
    }
    return 0;
}
