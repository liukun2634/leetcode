#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& nums, int left, int right);

void quick_sort(vector<int>& nums, int left, int right)
{
    if (left >= right)
        return;

    int mid = partition(nums, left, right);

    quick_sort(nums, left, mid - 1);
    quick_sort(nums, mid + 1, right);
}

//case 1: 3 4 5 2
// 3 2 5 4
// 2 3 5 4

int partition(vector<int>& nums, int left, int right)
{
    int pivot = left;

    int i = left, j = right;
    while (i < j) {
        while (i < j && nums[pivot] <= nums[j]) {
            j--;
        }
        while (i < j && nums[pivot] >= nums[i]) {
            i++;
        }
        swap(nums[i], nums[j]);
    }
    swap(nums[pivot], nums[i]);
    return i;
}

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    quick_sort(nums, 0, nums.size() - 1);

    for (int i = 0; i < n; i++) {
        cout << nums[i] << " ";
    }

    return 0;
}