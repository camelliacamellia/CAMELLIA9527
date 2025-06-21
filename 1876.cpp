// 简单题，重拳出击
class Solution {
public:
    int countGoodSubstrings(string s) {
        int num = 0;
        int n = s.length();
        for (int i = 2; i < n; i++)
        {
            if (s[i - 2] != s[i - 1] && s[i - 1] != s[i] && s[i - 2] != s[i])
                num++;
        }
        return num;
    }
};

// 最佳解一样的对吧
class Solution {
public:
    int countGoodSubstrings(string s) {
        if (s.size() < 3) {
            return 0;
        }
        int len = s.size();
        int cnt = 0;
        for (int i = 0; i < len - 2; i++) {
            int a = s[i];
            int b = s[i + 1];
            int c = s[i + 2];
            if (a != b && b != c && c != a) {
                cnt++;
            }
        }
        return cnt;

    }
};