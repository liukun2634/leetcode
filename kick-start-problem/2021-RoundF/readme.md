Festival:


注意：
使用两个数组，分别记录开始节点的happy值 和 结束节点的happy值。在遍历时，就是否达到开始和是否到达结束来操作一起的和。

multiset的使用 （可以存储多个相同值）
erase 的时候，不能使用value，这样会把所有的value删除。 要使用iterator（结合find找到第一个iterator）


```C++
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t += 1) {
        int D, N, K;
        cin >> D >> N >> K;
        vector<vector<int>> S(D + 1), E(D + 1);
        LL ans = 0, sum = 0;
        for (int i = 0, h, s, e; i < N; i += 1) {
            cin >> h >> s >> e;
            S[s].push_back(h);
            E[e].push_back(h);
        }
        multiset<int> ms, ns;
        for (int i = 1; i <= D; i += 1) {
            for (int x : S[i]) {
                sum += x;
                ms.insert(x);
                if ((int)ms.size() > K) {
                    sum -= *ms.begin();
                    ns.insert(*ms.begin());
                    ms.erase(ms.begin());
                }
            }
            ans = max(ans, sum);
            for (int x : E[i]) {
                if (ns.find(x) != ns.end()) ns.erase(ns.find(x));
                else {
                    sum -= x;
                    ms.erase(ms.find(x));
                    if (not ns.empty()) {
                        sum += *ns.rbegin();
                        ms.insert(*ns.rbegin());
                        ns.erase(ns.find(*ns.rbegin()));
                    }
                }
            }
        }
        cout << "Case #" << t << ": " << ans << "\n";
    }
    return 0;
}
```