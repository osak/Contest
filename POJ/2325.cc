//Name: Persistent Numbers
//Level: 3
//Category: 数論,多倍長,BigNum
//Note:

/*
 * 与えられた数値を素因数分解してから，その組み合わせで桁を構成していく．
 * 考えるべき素因数は1桁のもののみ．
 * 5と7は他の素因数と掛けて減らすことができないので，そのまま出力する．
 * 2と3の合成の優先順位は
 * ・2が3つあったら掛けて8にする(桁数はなるべく減らしたほうがよく，2つ減らせるのはこの組み合わせのみだから)
 * ・2が2つと3があったら2と6にする(1つ減らせる組の中では，なるべく小さい数字を生成したほうがよい)
 * ・2が2つあったら掛けて4にする
 * ・2と3があったら掛けて6にする
 * ・3が2つあったら掛けて9にする
 * これで各数字の出現回数を数えて，小さいほうから出力していけばよい．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int primes[] = {2,3,5,7};
const int PRIME_CNT = 4;

struct BigNum {
    vector<int> digits;

    BigNum(const string &num) {
        for(string::const_reverse_iterator it = num.rbegin(); it != num.rend(); ++it) {
            digits.push_back(*it - '0');
        }
    }

    bool is_one() const {
        if(digits[0] != 1) return false;
        for(vector<int>::const_iterator it = digits.begin()+1; it != digits.end(); ++it) {
            if(*it != 0) return false;
        }
        return true;
    }

    BigNum& operator /= (int n) {
        int acc = 0;
        for(vector<int>::reverse_iterator it = digits.rbegin(); it != digits.rend(); ++it) {
            acc += *it;
            *it = acc / n;
            acc %= n;
            acc *= 10;
        }
        return *this;
    }

    int operator % (int n) const {
        int acc = 0;
        for(vector<int>::const_reverse_iterator it = digits.rbegin(); it != digits.rend(); ++it) {
            acc += *it;
            acc %= n;
            acc *= 10;
        }
        return acc / 10;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true) {
        string digits;
        cin >> digits;
        if(digits[0] == '-') break;
        if(digits.size() == 1) {
            cout << "1" << digits << endl;
            continue;
        }

        BigNum num(digits);
        vector<int> prime_division(4, 0);
        for(int i = 0; i < 4; ++i) {
            while(num % primes[i] == 0) {
                num /= primes[i];
                ++prime_division[i];
            }
        }
        if(!num.is_one()) {
            cout << "There is no such number." << endl;
        } else {
            vector<int> res(10, 0);
            // add 2s
            res[8] += prime_division[0] / 3; // 2^3 = 8
            prime_division[0] %= 3;
            if(prime_division[0] == 2) {
                res[4]++;
                prime_division[0] = 0;
            }

            // if only 2 is remained, combine with 3 if number of 3 is odd.
            if(prime_division[0] > 0) {
                if(prime_division[1] % 2 == 1) {
                    res[6]++;
                    prime_division[1]--;
                } else {
                    res[2]++;
                }
                prime_division[0]--;
            }

            // add 3s
            res[9] += prime_division[1] / 2;
            prime_division[1] %= 2;
            if(prime_division[1] > 0) {
                res[3]++;
                prime_division[1]--;
            }

            // if there are 3 and 4 pair, convert to 2 and 6
            while(res[3] > 0 && res[4] > 0) {
                res[3]--; res[4]--;
                res[2]++; res[6]++;
            }

            // add 5 and 7s
            res[5] += prime_division[2];
            res[7] += prime_division[3];

            for(int i = 1; i <= 9; ++i) {
                for(int j = 0; j < res[i]; ++j) cout << i;
            }
            cout << endl;
        }
    }
    return 0;
}
