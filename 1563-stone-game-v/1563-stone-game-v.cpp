class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();

        // Prefix sum
        vector<int> prefix(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stoneValue[i];
        }

        // dp[i][j] = maximum score from i to j
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Length of subarray
        for (int len = 2; len <= n; len++) {

            for (int i = 0; i + len <= n; i++) {

                int j = i + len - 1;

                // Try every possible split
                for (int k = i; k < j; k++) {

                    int leftSum = prefix[k + 1] - prefix[i];
                    int rightSum = prefix[j + 1] - prefix[k + 1];

                    if (leftSum < rightSum) {

                        dp[i][j] = max(
                            dp[i][j],
                            leftSum + dp[i][k]
                        );

                    }
                    else if (leftSum > rightSum) {

                        dp[i][j] = max(
                            dp[i][j],
                            rightSum + dp[k + 1][j]
                        );

                    }
                    else {

                        dp[i][j] = max({
                            dp[i][j],
                            leftSum + dp[i][k],
                            rightSum + dp[k + 1][j]
                        });
                    }
                }
            }
        }

        return dp[0][n - 1];
    }
};