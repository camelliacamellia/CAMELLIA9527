// 要O(log n)时间复杂度？ 我管你这那的
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int n = arr.size() - 1;
        for (int i = 1; i <= n; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                return i;
            }
        }
        return n;
    }
};

// 最佳解，二分法
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = n - 1;
        int ll = (r - l) / 3, rr = (r - l) * 2 / 3;
        while (l < r) {
            if (nums[ll] < nums[rr]) {
                l = ll + 1;
            }
            else {
                r = rr;
            }
            ll = l + (r - l) / 3;
            rr = l + (r - l) * 2 / 3;
        }
        return l;
    }
};