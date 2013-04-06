#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

#define FOREACH(it,v) for(__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

struct TheSwapsDivOne {
    double find(const vector<string> &_seq, int k) {
        vector<double> seq;
        int sum = 0;
        FOREACH(it, _seq) {
            FOREACH(it2, *it) {
                seq.push_back(*it2 - '0');
                sum += seq.back();
            }
        }

        const int N = seq.size();
        double a = static_cast<double>(N*N - 3*N) / (N * (N-1));
        double b = 2.0 / (N*(N-1));
        cout << a << ' ' << b << endl;
        const double pa = pow(a, k);
        const double pb = a == 0 ? b : b * (1 - pa) / (1 - a);
        cout << pa << ' ' << pb << endl;
        double ans = 0;
        FOREACH(it, seq) {
            const int pos = distance(seq.begin(), it);
            *it = pa * (*it) + sum * pb;
            double ln = pos+1;
            double rn = N-pos;
            double prob = (ln*rn) / (N * (N-1) / 2.0 + N);
            cout << *it << ' ' << prob << endl;
            ans += *it * prob;
        }
        return ans;
    }
};

const string t1[] = {"4", "77"};
const string t2[] = {"4", "77"};
const string t3[] = {"1", "1", "1", "1", "1", "1", "1"};
const string t4[] = {"572685085149095989026478064633266980348504469", "19720257361", "9", "69"};
int main() {
    TheSwapsDivOne t;
    cout << t.find(vector<string>(t1, t1+2), 1) << endl;
    cout << t.find(vector<string>(t2, t2+2), 47) << endl;
    cout << t.find(vector<string>(t3, t3+7), 1000000) << endl;
    cout << t.find(vector<string>(t4, t4+4), 7) << endl;
}
