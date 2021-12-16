#include <iostream>
using namespace std;
const int maxn = 10000 + 1;
int X[maxn], Y[maxn];

int main()
{
    int k;
    while (cin >> k) {
        int ans = 0;
        for (int y = k + 1; y <= 2 * k; y++) {
            if (y * k % (y - k) == 0) {
                ans++;
                X[ans] = y * k / (y - k);
                Y[ans] = y;
            }
        }
        cout << ans << endl;
        for (int i = 1; i <= ans; i++) {
            cout << "1/" << k << " = "
                 << "1/" << X[i] << " + 1/" << Y[i] << endl;
        }
    }
    return 0;
}