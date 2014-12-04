//Name: Unit Converter
//Level: 2
//Category: 文字列
//Note:

/*
 * 数値を文字列として読み、指数表記に直す。
 * そのあと補助単位を処理する。
 *
 * オーダーは O(|S|)。
 */
#include <iostream>
#include <string>
#include <map>

using namespace std;

void solve() {
    map<string,int> dict;

    dict["yotta"] = 24;
    dict["zetta"] = 21;
    dict["exa"] = 18;
    dict["peta"] = 15;
    dict["tera"] = 12;
    dict["giga"] = 9;
    dict["mega"] = 6;
    dict["kilo"] = 3;
    dict["hecto"] = 2;
    dict["deca"] = 1;
    dict["deci"] = -1;
    dict["centi"] = -2;
    dict["milli"] = -3;
    dict["micro"] = -6;
    dict["nano"] = -9;
    dict["pico"] = -12;
    dict["femto"] = -15;
    dict["ato"] = -18;
    dict["zepto"] = -21;
    dict["yocto"] = -24;

    string num, prefix, unit;
    cin >> num >> prefix;
    if(dict.count(prefix)) {
        cin >> unit;
    } else {
        unit = prefix;
        prefix = "";
    }

    int e;
    string real;
    auto dot = num.find_first_of('.');
    if(dot == string::npos) {
        e = (int)num.size() - 1;
        real = num;
    } else {
        string int_part = num.substr(0, dot);
        if(int_part != "0") {
            real += int_part;
            real += num.substr(dot+1);
            e = (int)dot - 1;
        } else {
            auto first = num.find_first_not_of('0', dot+1);
            real = num.substr(first);
            e = (int)dot - first;
        }
    }
    e += dict[prefix];
    cout << real[0];
    if(real.size() > 1) {
        cout << '.' << real.substr(1);
    }
    cout << " * 10^" << e << ' ' << unit << endl;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    int N;
    cin >> N;
    while(N--) solve();
    return 0;
}
