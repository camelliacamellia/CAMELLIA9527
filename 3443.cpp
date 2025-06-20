// 贪心 ，在每一个移动以后计算在该处的最佳方法，是按前一步走还是在这一步进行转向。
class Solution {
public:
    int maxDistance(string s, int k) {
        vector<int>A(4, 0);
        int n = s.length();
        int num = 0;
        for (int i = 0; i < n; i++)
        {
            int a = int(s[i]);
            switch (a)
            {
            case 78:
                A[0]++;
                break;
            case 83:
                A[1]++;
                break;
            case 69:
                A[2]++;
                break;
            case 87:
                A[3]++;
                break;
            default:
                break;
            }
            int maxx = max(A[0], A[1]) + max(A[2], A[3]);
            int minn = min(A[0], A[1]) + min(A[2], A[3]);
            num = max(num, maxx - minn + 2 * min(minn, k));
        }
        return num;
    }
};

// 最佳解差不多,但是好看很多
class Solution {
public:
    int maxDistance(string s, int k) {
        int x = 0, y = 0, ans = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            switch (s[i])
            {
            case 'N': ++y; break;
            case 'S': --y; break;
            case 'E': ++x; break;
            case 'W': --x; break;
            }
            ans = max(ans, min(abs(x) + abs(y) + 2 * k, i + 1));
        }
        return ans;
    }
};