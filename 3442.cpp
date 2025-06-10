//      使用一个26大小的数组记录每个字母出现的次数，然后遍历数组找出满足条件的最大最小值
//      把两个if改成if else可以达到最快的题解
class Solution {
public:
    int maxDifference(string s) {
        int A[26] = { 0 };
        int n = s.length();
        for (int i = 0; i < n; i++)
        {
            A[int(s[i]) - 'a']++;
        }
        int a = INT_MAX, b = INT_MIN;
        for (int i = 0; i < 26; i++)
        {
            if (A[i] > b && A[i] % 2 == 1)
                b = A[i];
            if (A[i] < a && A[i] != 0 && A[i] % 2 == 0)
                a = A[i];
        }
        return b - a;
    }
};