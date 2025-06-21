// 本来是直接使用排列组合，过了大部分案例，但是有一些过不了，只能算是敲一段排列组合的实现。
class Solution {
public:
    int countGoodArrays(int n, int m, int k) {
        int a = 1;
        long long num = 0;
        num += m * (C(n - 1, k) * power(m - 1, n - 1 - k)) % (1000000007);
        return num;
    }
    int C(int m, int n)
    {
        int num = 1;
        int i = 1;
        while (i <= n)
        {
            num *= m-- / i++;
        }
        return num;
    }
    int power(int m, int n)
    {
        long long num = 1;
        while (--n >= 0)
        {
            num = (num * m) % (1000000007);
        }
        return num;
    }
};



// 官方解

const int MOD = 1e9 + 7;
const int MX = 1e5;

long long fact[MX];
long long inv_fact[MX];

class Solution {
    long long qpow(long long x, int n) {
        long long res = 1;
        while (n) {
            if (n & 1) {
                res = res * x % MOD;
            }
            x = x * x % MOD;
            n >>= 1;
        }
        return res;
    }

    long long comb(int n, int m) {
        return fact[n] * inv_fact[m] % MOD * inv_fact[n - m] % MOD;
    }
    void init() {
        if (fact[0]) {
            return;
        }
        fact[0] = 1;
        for (int i = 1; i < MX; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        inv_fact[MX - 1] = qpow(fact[MX - 1], MOD - 2);
        for (int i = MX - 1; i; i--) {
            inv_fact[i - 1] = inv_fact[i] * i % MOD;
        }
    }

public:
    int countGoodArrays(int n, int m, int k) {
        init();
        return comb(n - 1, k) * m % MOD * qpow(m - 1, n - k - 1) % MOD;
    }
};
