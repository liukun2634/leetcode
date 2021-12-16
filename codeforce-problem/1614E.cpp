#include <iostream>
#include <vector>
using namespace std;
int MOD = 1e9 + 1;

int main()
{
    int n, k, X;
    cin >> n;
    vector<int> T(n);
    int lastans = 0;
    for (int i = 0; i < n; i++) {
        cin >> T[i];
        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> X;
            int lastans = (X + lastans) % MOD;
            for (int t = 0; t <= i; t++) {
                if (T[t] < lastans) {
                    lastans--;
                } else if (T[t] > lastans) {
                    lastans++;
                }
            }
            cout << lastans << endl;
        }
    }
    return 0;
}