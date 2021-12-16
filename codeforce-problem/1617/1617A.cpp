#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void print(char x, int n)
{
    for (int i = 0; i < n; i++) {
        cout << x;
    }
}

int main()
{
    int t;
    cin >> t;
    for (int c = 0; c < t; c++) {
        string s, T;
        cin >> s >> T;
        vector<int> cnt(26, 0);
        int n = s.size();
        for (int i = 0; i < n; i++) {
            cnt[s[i] - 'a']++;
        }

        if (T == "abc" && (cnt[0] != 0 && cnt[1] != 0 && cnt[2] != 0)) {
            print('a', cnt[0]);
            print('c', cnt[2]);
            print('b', cnt[1]);
            for (int i = 3; i < 26; i++) {
                print('a' + i, cnt[i]);
            }
        } else {
            for (int i = 0; i < 26; i++) {
                print('a' + i, cnt[i]);
            }
        }
        cout<<endl;
    }
    return 0;
}