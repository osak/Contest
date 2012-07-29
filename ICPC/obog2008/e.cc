#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

vector<string> v(10);
vector<bool> used(10, false);
int N;
int bestlen;
string bestans;

string concat(const string &s1, const string &s2) {
	string tmp = s1;
	for(int i = s2.size(); i >= 0; --i) {
		if(s1.size() < i) continue;
		int start = s1.size()-i;
		bool ok = true;
		for(int j = 0; j < i; ++j) {
			if(s1[start+j] != s2[j]) {
				ok = false;
				break;
			}
		}
		if(ok) {
			tmp += s2.substr(i);
			return tmp;
		}
	}
	return s1+s2;
}

void dfs(int depth, string str) {
	if(depth == N) {
		if(str.size() <= bestlen) {
            if(str.size() == bestlen && str > bestans) return;
			bestlen = str.size();
			bestans = str;
		}
		return;
	}
	for(int i = 0; i < N; ++i) {
		if(used[i]) continue;
        string s = str;
		if(s.find(v[i]) == -1) s = concat(str, v[i]);
	//	cout << s << endl;
		used[i] = true;
		dfs(depth+1, s);
		used[i] = false;
	}
}

int main() {
    /*
	cout << concat("", "asdf") << endl;
    cout << concat("asdfasdf", "asdf") << endl;
    cout << concat("adsf", "adsfasdf") << endl;
    cout << concat("abcde", "abcde") << endl;
    cout << concat("qwerty", "rty") << endl;
    cout << concat("qwerty", "rtyasdf") << endl;
    cout << concat("qwerty", "yasdf") << endl;
    */
	while(true) {
		cin >> N;
		if(N == 0) break;

		for(int i = 0; i < N; ++i) {
			cin >> v[i];
			used[i] = false;
		}
		bestlen = INT_MAX;
		dfs(0, "");
		cout << bestans << endl;
	}

	return 0;
}
