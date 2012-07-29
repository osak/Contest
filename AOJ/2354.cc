#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

bool cmp(const pair<int,int> &a, const pair<int,int> &b) {
    return (double)a.second / a.first > (double)b.second / b.first;
}

int main() {
    ios::sync_with_stdio(0);

    int N, W;
    cin >> N >> W;

    double ans = 0;
    int rem = W;
    vector<pair<int,int> > posv, negv;
    for(int i = 0; i < N; ++i) {
        int w, vv;
        cin >> w >> vv;
        if(w <= 0 && vv >= 0) {
            ans += vv;
            rem -= w;
        }
        else if(w >= 0 && vv <= 0) {
            // through
        }
        else {
            if(w > 0) posv.push_back(make_pair(w, vv));
            else negv.push_back(make_pair(-w, -vv));
        }
    }
    sort(posv.begin(), posv.end(), cmp);
    sort(negv.begin(), negv.end(), cmp);
    reverse(negv.begin(), negv.end());

    double pr, nr;
    vector<pair<int,int> >::iterator pi, ni;
    pi = posv.begin();
    ni = negv.begin();
    pr = 0;
    if(ni != negv.end()) nr = ni->first;

    while(pi != posv.end()) {
        if(rem < pi->first) {
            ans += (double)pi->second * rem / pi->first;
            pr = pi->first - rem;
            rem = 0;
            break;
        }
        else {
            ans += pi->second;
            rem -= pi->first;
            ++pi;
        }
    }

    while(pi != posv.end() && ni != negv.end()) {
        bool pr_is_min = pr < nr;
        double amt_w = pr_is_min ? pr : nr;

        double diff = amt_w/pi->first*pi->second - amt_w/ni->first*ni->second;
        if(diff < 0) break;
        ans += diff;
        if(pr_is_min) {
            ++pi;
            pr = pi->first;
            nr -= amt_w;
        }
        else {
            ++ni;
            nr = ni->first;
            pr -= amt_w;
        }
    }

    cout.precision(4);
    cout.setf(ios::fixed);
    cout << ans << endl;

    return 0;
}
