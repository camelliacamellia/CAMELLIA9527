class Solution {
public:
    int percentageLetter(string s, char letter) {
        int A[26] = {0};
        int n = s.length();
        for(int i = 0 ; i < n ; i++)
        {
            A[int(s[i])-'a']++;
        }
        return A[letter-'a']*100/n;
    }
};
