#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int findKth(vector<int>& nums1, int n, vector<int>& nums2, int m, int k)
{
    int index1 = 0;
    int index2 = 0;
    while (true) {
        if (index1 == n) {
            return nums2[index2 + k - 1];
        }

        if (index2 == m) {
            return nums1[index1 + k - 1];
        }

        if (k == 1) {
            return min(nums1[index1], nums2[index2]);
        }

        int newIndex1 = min(n - 1, index1 + k / 2 - 1);
        int newIndex2 = min(m - 1, index2 + k / 2 - 1);
        if (nums1[newIndex1] < nums2[newIndex2]) {
            k = k - (newIndex1 - index1 + 1);
            index1 = newIndex1 + 1;
        } else {
            k = k - (newIndex2 - index2 + 1);
            index2 = newIndex2 + 1;
        }
    }
}

double solve(vector<int>& nums1, vector<int>& nums2)
{
    int n = nums1.size();
    int m = nums2.size();
    if ((m + n) % 2 == 1) {
        return findKth(nums1, n, nums2, m, (m + n) / 2 + 1);
    } else {
        return (findKth(nums1, n, nums2, m, (m + n) / 2) + findKth(nums1, n, nums2, m, (m + n) / 2 + 1)) / 2.0;
    }
}

int main()
{
    int n, m;
    cin >> n;
    vector<int> nums1(n);
    for (int i = 0; i < n; i++) {
        cin >> nums1[i];
    }
    cin >> m;
    vector<int> nums2(m);
    for (int i = 0; i < m; i++) {
        cin >> nums2[i];
    }
    cout << "median: " << solve(nums1, nums2) << endl;
    return 0;
}