class Solution {
public:
    unordered_set<string> result;

    void solve(string &s, int index, int left,
               int right, int balance, string current) {

        if (index == s.length()) {
            if (left == 0 && right == 0 && balance == 0) {
                result.insert(current);
            }
            return;
        }

        char c = s[index];

        // Case 1: Parenthesis
        if (c == '(') {

            // Remove '('
            if (left > 0) {
                solve(s, index + 1, left - 1,
                      right, balance, current);
            }

            // Keep '('
            solve(s, index + 1, left,
                  right, balance + 1, current + c);
        }

        else if (c == ')') {

            // Remove ')'
            if (right > 0) {
                solve(s, index + 1, left,
                      right - 1, balance, current);
            }

            // Keep ')' only if it doesn't make balance negative
            if (balance > 0) {
                solve(s, index + 1, left,
                      right, balance - 1, current + c);
            }
        }

        else {
            // Letter
            solve(s, index + 1, left,
                  right, balance, current + c);
        }
    }

    vector<string> removeInvalidParentheses(string s) {

        int left = 0, right = 0;

        // Find minimum removals required
        for (char c : s) {
            if (c == '(') {
                left++;
            }
            else if (c == ')') {
                if (left > 0)
                    left--;
                else
                    right++;
            }
        }

        solve(s, 0, left, right, 0, "");

        return vector<string>(result.begin(), result.end());
    }
};