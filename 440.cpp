
// 功能可以实现，但是超时了，每日一尽力+cv

// 功能可以实现，但是超时了，每日一尽力
>>>>>>> 75f5c859e3604e91f7e8c361287f8602a39e6247
class Solution {
public:
    int findKthNumber(int n, int k) {
        long long ans;
        long long num = 1;
        int i = 0;
        while(i++<k)
        {
            ans = num;
            if(num*10<=n)
                num*=10;
            else
            {
                while(num%10==9 || num+1>n)
                    num/=10;
                num++;
            }
        }
        return ans;
    }
};


// 官方解
class Solution {
public:
    int getSteps(int curr, long n) {
        int steps = 0;
        long first = curr;
        long last = curr;
        while (first <= n) {
            steps += min(last, n) - first + 1;
            first = first * 10;
            last = last * 10 + 9;
        }
        return steps;
    }

    int findKthNumber(int n, int k) {
        int curr = 1;
        k--;
        while (k > 0) {
            int steps = getSteps(curr, n);
            if (steps <= k) {
                k -= steps;
                curr++;
            } else {
                curr = curr*10;
                k--;
            }
        }
        return curr;
    }
};
