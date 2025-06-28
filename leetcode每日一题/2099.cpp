// 日常丑陋代码
bool emp(pair<int, int>A, pair<int, int>B)
{
    return A.first > B.first;
}
bool emp1(pair<int, int>A, pair<int, int>B)
{
    return A.second < B.second;
}
class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        int n = nums.size();
        vector<pair<int, int>>ans;
        vector<pair<int, int>>ans1;
        for (int i = 0; i < n; i++)
        {
            ans.push_back(pair<int, int>(nums[i], i));
        }
        sort(ans.begin(), ans.end(), emp);
        vector<int>path(k);
        for (int i = 0; i < k; i++)
        {
            ans1.push_back(pair<int, int>(ans[i].first, ans[i].second));
        }
        sort(ans1.begin(), ans1.end(), emp1);
        for (int i = 0; i < k; i++)
        {
            path[i] = nums[ans1[i].second];
        }
        return path;
    }
};

// 最佳解好像差不多，平衡了
class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> index(nums.size());
        iota(index.begin(), index.end(), 0);
        sort(index.begin(), index.end(), [&nums](int l, int r) {
            return nums[l] > nums[r];
            });
        vector<int> selected(index.begin(), index.begin() + k);
        sort(selected.begin(), selected.end());
        vector<int> ans;
        ans.reserve(k);
        for (int s : selected) {
            ans.push_back(nums[s]);
        }
        return ans;
    }
};