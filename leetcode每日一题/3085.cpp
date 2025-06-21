// �ȼ�¼ÿ����ĸ�ĳ��ִ�����Ȼ�����������������26*26�ĸ��Ӷ�
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

// ��ѽ�ʹ��һ��max_save��¼���ֵ��������ʹ��һ��sort��ͬʱ���ranges::sort��ֱ��ʹ��sortЧ�ʸ�һ�㣬����devc++����ʹ�ã��
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
                sum += min(cnt[j], cnt[i] + k); // ���ౣ�� cnt[i]+k ��
            }
            max_save = max(max_save, sum);
        }

        return word.length() - max_save;
    }
};