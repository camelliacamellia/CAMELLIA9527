// ��Ŀ˵Ҫ�����У���ʵ���ϲ���Ҫ��������У�ֻ��Ҫ���һ�����֣�����ֱ�����򰴴�С�����жϾ���
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

// ���Ž�Ҳ���
class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        int res = 1, minN = ranges::min(nums), maxN = ranges::max(nums);
        vector<bool> dict(maxN + 1); // Ĭ�ϳ�ʼ����Ϊfalse
        for (int i : nums) dict[i] = true;
        for (int i = minN, j = i; j <= maxN; ++j)
            if (dict[j] && j - i > k) i = j, ++res;
        return res;
    }
};