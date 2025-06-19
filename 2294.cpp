// 题目说要子序列，但实际上不需要输出子序列，只需要输出一个数字，所以直接排序按大小进行判断就行
class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int count = 1;
        int p = nums[0];
        int n = nums.size();
        for (int i = 1; i < n; i++)
        {
            if (nums[i] - k > p)
            {
                count++;
                p = nums[i];
            }
        }
        return count;
    }
};

// 最优解也差不多
class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        int res = 1, minN = ranges::min(nums), maxN = ranges::max(nums);
        vector<bool> dict(maxN + 1); // 默认初始化都为false
        for (int i : nums) dict[i] = true;
        for (int i = minN, j = i; j <= maxN; ++j)
            if (dict[j] && j - i > k) i = j, ++res;
        return res;
    }
};