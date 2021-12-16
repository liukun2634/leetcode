#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int T, n, k;
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin>>n>>k;
        vector<int> nums(n);
        for(int i = 0; i < n; i++){
            cin>>nums[i];
        }

        sort(nums.begin(), nums.end());
        int res = 0;
        for(int j = 0; j < k; j++){
            res += nums[n - 1 - j - k] / nums[n - 1 - j];
        }
        for(int i = 0; i < n - 2 * k; i++){
            res += nums[i];
        }
        cout<<res<<endl;

    }
    return 0;
}