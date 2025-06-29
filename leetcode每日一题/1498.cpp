// 使用双指针 定义一个left，right在排好序的数组的头尾处
// 再定义一个幂计算函数
class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        int n = nums.size();
        long long num = 0;
        sort(nums.begin(), nums.end());
        int left = 0;
        int right = n - 1;
        while (left <= right)
        {
            int sum = nums[left] + nums[right];
            if (sum <= target)
            {
                num += intPow(2, right - left);
                left++;
            }
            else
                right--;
        }
        return  num % 1000000007;
    }
    long long intPow(long long a, long long b) {
        int res = 1;
        static constexpr int MOD = 1000000007;
        a %= MOD;
        while (b > 0) {
            if (b & 1) {
                res = (res * a) % MOD;
            }
            a = (a * a) % MOD;
            b >>= 1;
        }
        return res;
    }
};