#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

long long reverse(long long x)
{
    long long res = 0;
    for (int i = 0; i < 64 && x > 0; ++i) {
        res |= (x & 1) << (63 - i);
        x >>= 1;
    }
    return res;
}

long long rev(long long x)
{
    int m = 0;
    while (x >= (1LL << m))
        ++m;
    long long ans = 0;
    for (int i = 0; i < m; ++i)
        if (x & (1LL << i))
            ans += (1LL << (m - i - 1));
    return ans;
}

bool solve(long long x, long long y, unordered_map<long long, bool>& cache)
{
    if (x > 2e18){
        cache[x] = false;
        return false;
    }
        
    if (x == y) {
        cache[x] = true;
        return true;
    }
        
    if (cache.count(x))
        return cache[x];
    bool flag = false;
    long long next = rev(2 * x);
    if (solve(next, y, cache)) {
        flag = true;
        return true;
    }

    next = rev(2 * x + 1);
    if (solve(next, y, cache)) {
        flag = true;
    }

    cache[x] = flag;
    return flag;
}

int main()
{
    long long x, y;
    cin >> x >> y;
    unordered_map<long long, bool> cache;
    string s = solve(x, y, cache) ? "YES" : "NO";
    cout << s;
    return 0;
}