#include <iostream>
#include <string>
using namespace std;

int main()
{
    int T, n;
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin>>n;
        string res = "";
        string s;
        int idx = -1;
        for(int i = 0; i < n - 2; i++){
            cin>> s;
            if(idx == 0 || res[idx] != s[0]) {
                res += s;
                idx += 2;
            } else {
                res += s[1];
                idx += 1;
            }
        }
        if(idx < n - 1) res += 'a';
        cout<<res<<endl;
    }
    return 0;
}