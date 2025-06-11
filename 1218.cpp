// �ҵĶ�̬�滮�ⷨ����ÿ��λ����Ѱ��ǰ����������������Ԫ�أ�ʱ�临�Ӷ�O(n^2)���ռ临�Ӷ�O(n)
// ���ǳ�ʱ�ˣ��ŵ��Ǵ�����׶���������С���ݷ�Χ��ʹ�ú�devc++��ʹ�����С�

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

// �ٷ��� ʹ��unordered_map ����devc++����ʹ�ã�������Ч���
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

