// 先记录每个字母的出现次数，然后暴力遍历，反正最大26*26的复杂度
class Solution {
public:
    int minimumDeletions(string word, int k) {
        vector<int>ans(26, 0);
        vector<int>path;
        int n = word.size();
        for (int i = 0; i < n; i++)
        {
            ans[int(word[i]) - 'a']++;
        }
        sort(ans.begin(), ans.end());
        for (int i = 0; i < 26; i++)
        {
            int a = ans[i];
            for (int j = i + 1; j < 26; j++)
            {
                a += min(ans[j], ans[i] + k);
            }
            path.push_back(a);
        }
        sort(path.begin(), path.end());
        return word.length() - path.back();
    }
};

// 最佳解使用一个max_save记录最大值，比我少使用一个sort，同时这个ranges::sort比直接使用sort效率高一点，但是devc++不能使用，猝
class Solution {
public:
    int minimumDeletions(string word, int k) {
        int cnt[26]{};
        for (char c : word) {
            cnt[c - 'a']++;
        }
        ranges::sort(cnt);

        int max_save = 0;
        for (int i = 0; i < 26; i++) {
            int sum = 0;
            for (int j = i; j < 26; j++) {
                sum += min(cnt[j], cnt[i] + k); // 至多保留 cnt[i]+k 个
            }
            max_save = max(max_save, sum);
        }

        return word.length() - max_save;
    }
};