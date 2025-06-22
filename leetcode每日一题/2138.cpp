
// 简单题直接暴力 ，O(n) + O(n)
class Solution {
public:
    vector<string> divideString(string s, int k, char fill) {
        int n = (s.length() / k + 0.99999);
        vector<string>ans;
        int i = 0;
        while (i < s.length())
        {
            int a = k;
            string ss;
            while (a-- && i < s.length())
            {
                ss += s[i++];
            }
            while (ss.length() < k)
            {
                ss.push_back(fill);

            }
            ans.push_back(ss);
        }
        return ans;
    }
};