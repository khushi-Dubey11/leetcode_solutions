class Solution {
public:
    int distinctSubseqII(string s) {
        const int MOD = 1e9 + 7;

        vector<long long> dp(26, 0);

        for (char c : s) {
            int x = c - 'a';

            long long total = 0;

            for (long long v : dp)
                total = (total + v) % MOD;

            dp[x] = (total + 1) % MOD;
        }

        long long ans = 0;

        for (long long v : dp)
            ans = (ans + v) % MOD;

        return ans;
    }
};