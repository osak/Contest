//Name: Flowers
//Level: 3
//Category: 貪欲,Greedy,Priority queue
//Note:

/**
 * 水をWリットル与えてから、それぞれの花ごとに肥料で調整していくので、Wを決定すれば全体のコストも求められる。
 * WをΔWだけ増やすと、それぞれの花で後で必要な肥料の量がvwΔW / vfだけ減少するから、肥料のコストはpf × vwΔW / vfだけ減少する
 * （vwが負の場合、コストは増加することになる）。
 * また、水そのものの費用がpwΔWだけかかる。
 *
 * 水を増やしていくと発生するイベントは
 * ・ある花のvitalityがthを超え、肥料のコストが影響しなくなる。
 * ・ある花のvitalityがthを割り、それまで必要のなかった肥料を増やす必要が出てくる。
 * これらのいずれも、水やりのコストを上げる方向に作用する。
 * したがって、ΔWの係数 pw - Σpf_i × vw_i / vf_i は水やりを進めるにしたがって単調増加していく。
 * この係数が負になっている間は、水やりを続けると得をするが、正になると肥料のみに切り替えたほうがよくなる。
 *
 * このようなイベントが発生する時刻は固定なので、あらかじめ求めてからソートしておき、係数の変化をシミュレーションすればよい。
 * オーダーは O(N log N)。
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;
    
    double PW;
    cin >> PW;
    vector<pair<double,double>> ds;
    double ans = 0;
    double cur_eff = PW;
    for(int i = 0; i < N; ++i) {
        double vw, pf, vf, th;
        cin >> vw >> pf >> vf >> th;
        if(th >= 0) ans += th / vf * pf;
        const double t = th / vw;
        const double eff = pf * vw / vf;
        if(th >= 0 && vw > 0) {
            ds.emplace_back(t, eff);
            cur_eff -= eff;
        } else if(th <= 0 && vw < 0) {
            ds.emplace_back(t, -eff);
        } else if(th >= 0 && vw < 0) {
            cur_eff -= eff;
        }
    }
    sort(begin(ds), end(ds));
    double prev = 0;
    for(auto &d : ds) {
        if(cur_eff > 0) break;
        //cout << cur_eff << ": " << ans << endl;
        ans += cur_eff * (d.first - prev);
        cur_eff += d.second;
        prev = d.first;
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
