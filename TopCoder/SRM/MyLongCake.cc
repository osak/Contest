//Name: MyLongCake
//Level: 3
//Category: 数学,Math
//Note: SRM617 Div1 Easy

/**
 * 長さが(N/約数)の倍数になっている点では必ず切らないといけない
 * （そうしないと、その約数で分配するときに超過が出てしまう）。
 * そのような場所をすべて数え上げればよい。
 *
 * オーダーはO(N sqrt N)。
 */
#include <set>
#include <iostream>

using namespace std;

struct MyLongCake {
    int cut(int N) {
        set<int> divisors;
        int tmp = N;
        divisors.insert(tmp);
        for(int i = 2; i <= tmp; ++i) {
            if(tmp % i == 0) {
                divisors.insert(i);
                divisors.insert(tmp / i);
                tmp /= i;
            }
        }
        divisors.erase(1);
        int res = 0;
        for(int i = 1; i <= N; ++i) {
            for(int d : divisors) {
                if(i % d == 0) {
                    ++res;
                    break;
                }
            }
        }
        return res;
    }
};

int main() {
    MyLongCake m;
    cout << m.cut(30) << endl;
    return 0;
}
