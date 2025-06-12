// 今日份的甜枣，我重拳出击
class Solution {
public:
    int maxAdjacentDistance(vector<int>& nums) {
        int val = abs(nums[0] - nums.back());
        int n = nums.size() - 1;
        for (int i = 0; i < n; i++)
        {
            if (abs(nums[i] - nums[i + 1]) > val)
                val = abs(nums[i] - nums[i + 1]);
        }
        return val;
    }
};

// 最佳解，也是大差不差
class Solution {
public:
    int maxAdjacentDistance(vector<int>& nums) {
        int ans = abs(nums[1] - nums[0]);
        for (int i = 0; i < nums.size(); i++) {
            ans = max(ans, abs(nums[i] - nums[(i + 1) % nums.size()]));
        }
        return ans;
    }
};