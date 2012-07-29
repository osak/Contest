//Name: Best Pizza
//Level: 2
//Category: 貪欲,Greedy
//Note:

/*
 * どのトッピングを載せても値段の増分は同じなので，最もカロリーが高いものから載せていくと最高のコストパフォーマンスになる．
 * (k個のトッピングを載せていて i(i≦k) 番目に高いものが選ばれておらず代わりに j(j>k) 番目が選ばれているとき，
 *  j番目をi番目に置換することでコストが変化しないままカロリーだけが高くなる．)
 */
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

int toppings[100];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, A, B, C;
    cin >> N >> A >> B >> C;
    for(int i = 0; i < N; ++i) {
        cin >> toppings[i];
    }
    sort(toppings, toppings+N, greater<int>());

    int total_cal = C, total_cost = A;
    int best = total_cal / total_cost;
    for(int i = 0; i < N; ++i) {
        total_cal += toppings[i];
        total_cost += B;
        best = max(best, total_cal / total_cost);
    }
    cout << best << endl;
    return 0;
}
