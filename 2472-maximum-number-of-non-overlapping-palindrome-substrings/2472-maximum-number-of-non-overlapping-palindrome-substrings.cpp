class Solution {
public:
    int maxPalindromes(string s, int k) {

        int n = s.size();

        // isPal[l][r] = true if s[l...r] is a palindrome
        vector<vector<bool>> isPal(n, vector<bool>(n, false));

        // Every single character is a palindrome
        for (int i = 0; i < n; i++) {
            isPal[i][i] = true;
        }

        // Check longer substrings
        for (int len = 2; len <= n; len++) {

            for (int l = 0; l + len <= n; l++) {

                int r = l + len - 1;

                if (s[l] == s[r]) {

                    if (len == 2)
                        isPal[l][r] = true;
                    else
                        isPal[l][r] = isPal[l + 1][r - 1];
                }
            }
        }

        // dp[i] = maximum palindromes using first i characters
        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= n; i++) {

            // Don't use character i-1
            dp[i] = dp[i - 1];

            // Try every substring ending at i-1
            for (int j = 0; j <= i - k; j++) {

                if (isPal[j][i - 1]) {

                    dp[i] = max(dp[i],
                                dp[j] + 1);
                }
            }
        }

        return dp[n];
    }
};