// 简单题，直接暴力 时间复杂度为O(n^2)
class Solution {
public:
    int maximumDifference(vector<int>& nums) {
        int maxx = -1;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (maxx < nums[j] - nums[i] && nums[j]>nums[i])
                    maxx = nums[j] - nums[i];
            }
        }
        return maxx;
    }
};

// 最优解 使用一个数组记录在该值前的最小值 时间复杂度为O(n)
class Solution {
public:
    int maximumDifference(vector<int>& nums) {
        int length = nums.size();
        vector<int> prefix(length, 0);
        prefix[0] = nums[0];
        for (int i = 1; i < length; i++) {
            prefix[i] = min(prefix[i - 1], nums[i]);
        }

        int maxDiff = -1, maxNum = 0;
        for (int i = length - 1; i > 0; i--) {
            maxNum = max(maxNum, nums[i]);
            if (maxNum > prefix[i - 1])
                maxDiff = max(maxDiff, maxNum - prefix[i - 1]);
        }

        return maxDiff;
    }
};