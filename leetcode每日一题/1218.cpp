// 我的动态规划解法，在每个位置上寻找前面所有满足条件的元素，时间复杂度O(n^2)，空间复杂度O(n)
// 但是超时了，优点是代码简单易懂，可以在小数据范围内使用和devc++上使用运行。

class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        int n = arr.size();
        vector<int>ans(n + 2, 1);
        int maxlength = INT_MIN;
        for (int i = 1; i < n; i++)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                if (arr[j] + difference == arr[i])
                {
                    ans[i] = ans[j] + 1;
                    break;
                }
            }
            maxlength = max(maxlength, ans[i]);
        }
        return maxlength;
    }
};

// 官方解 使用unordered_map 但是devc++不能使用，竞赛无效，猝
class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        int ans = 0;
        unordered_map<int, int> dp;
        for (int v : arr) {
            dp[v] = dp[v - difference] + 1;
            ans = max(ans, dp[v]);
        }
        return ans;
    }
};

