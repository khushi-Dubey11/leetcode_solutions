class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();

        // Step 1: Precompute all proper divisors
        vector<vector<int>> factors(n + 1);

        for (int i = 1; i <= n; i++) {
            factors[i].push_back(1);
        }

        for (int d = 2; d < n; d++) {
            for (int i = d * 2; i <= n; i += d) {
                factors[i].push_back(d);
            }
        }

        // Step 2: Calculate cost of every substring
        // cost[i][j] = minimum changes to make s[i...j]
        // a semi-palindrome
        vector<vector<int>> cost(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                int len = j - i + 1;
                int minCost = n;

                for (int d : factors[len]) {

                    int changes = 0;

                    for (int offset = 0; offset < d; offset++) {

                        int l = i + offset;
                        int r = j - d + 1 + offset;

                        while (l < r) {

                            if (s[l] != s[r]) {
                                changes++;
                            }

                            l += d;
                            r -= d;
                        }
                    }

                    minCost = min(minCost, changes);
                }

                cost[i][j] = minCost;
            }
        }

        // Step 3: Dynamic Programming
        // dp[i][j] = minimum changes to divide
        // s[i...n-1] into exactly j semi-palindromes

        const int INF = 1e9;

        vector<vector<int>> dp(
            n + 1, vector<int>(k + 1, INF)
        );

        dp[n][0] = 0;

        for (int i = n - 1; i >= 0; i--) {

            for (int j = 1; j <= k; j++) {

                // Last substring must have length >= 2
                for (int l = i + 1; l < n; l++) {

                    if (dp[l + 1][j - 1] == INF) {
                        continue;
                    }

                    dp[i][j] = min(
                        dp[i][j],
                        cost[i][l] + dp[l + 1][j - 1]
                    );
                }
            }
        }

        return dp[0][k];
    }
};