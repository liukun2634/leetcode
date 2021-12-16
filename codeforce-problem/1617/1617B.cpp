#include <algorithm>
#include <iostream>
using namespace std;

void solve(int m)
{
    int a, b, c;
    for (int i = m; i > 1; i--) {
        if (m % i == 0) {
            int c = m / i;
            for (int a = 2 * c; a < m; a = a + c) {
                int b = m - a - c;
                if (__gcd(a, b) == c && a != b && a != b && a != c) {
                    cout << a << " " << b << " " << c << " " << endl;
                    return;
                }
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        solve(m);
    }

    return 0;
}