//Name: Sum of Integers
//Level: 1
//Category: 全探索
//Note:

/*
 * next_permutationは全てのcombinationを列挙するのに使える。
 */
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    while(true) {
        int N, S;
        cin >> N >> S;
        if(!N && !S) break;

        int arr[10] = {0};
        for(int i = 0; i < N; ++i) arr[9-i] = 1;
        int cnt = 0;
        do {
            int sum = 0;
            for(int i = 0; i < 10; ++i)
                if(arr[i]) sum += i;
            if(sum == S) ++cnt;
        } while(next_permutation(arr, arr+10));

        cout << cnt << endl;
    }
    return 0;
}
