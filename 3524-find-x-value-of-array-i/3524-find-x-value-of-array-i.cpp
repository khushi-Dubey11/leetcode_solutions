class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);
        vector<long long> dp(k, 0);

        for (int num : nums) {
            vector<long long> next(k, 0);

            // Start a new subarray with only num
            next[num % k]++;

            // Extend all previous subarrays
            for (int r = 0; r < k; r++) {
                int newRemainder = (r * (num % k)) % k;
                next[newRemainder] += dp[r];
            }

            dp = next;

            // Every subarray ending here contributes to answer
            for (int r = 0; r < k; r++) {
                ans[r] += dp[r];
            }
        }

        return ans;
    }
};