#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> nums(7);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 7; j++) {
            cin >> nums[j];
        }
        int a1 = nums[0], a2 = nums[1], a3 = (a1 + a2 == nums[2] ? nums[3] : nums[2]);
        cout << a1 << " " << a2 << " " << a3 << endl;
    }
    return 0;
}