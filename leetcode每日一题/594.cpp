// �����Ǽ��⵫�Ǿ��Ǹо��ѣ����������ֳ���������������
class Solution {
public:
    int findLHS(vector<int>& nums) {
        map<int, int>mp;
        int num = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            mp[nums[i]]++;
        }
        for (auto it = mp.begin(); it != mp.end(); it++)
        {
            auto itt = std::next(it);
            if (itt != mp.end() && abs(itt->first - it->first) == 1)
            {
                num = max(num, itt->second + it->second);
            }
        }
        return num;
    }
};

// ��ѽ⣬��֪ʶ auto &[x,y]:cnt ���Դ�������ָ�룬һ��ָ��valueһ��ָ��ָ��key

class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> cnt;
        for (int x : nums) cnt[x]++;
        int ans = 0;
        for (auto& [x, c] : cnt) {
            if (cnt.contains(x + 1)) {
                ans = max(ans, c + cnt[x + 1]);
            }
        }
        return ans;
    }
};