class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        bool sorted = true;

        for (int i = 1; i < n; i++) {
            if (s[i] < s[i - 1]) {
                sorted = false;
                break;
            }
        }

        // Already sorted
        if (sorted) return 0;

        // Cannot sort a reversed string of length 2
        if (n == 2) return -1;

        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());

        // Minimum is at the beginning or maximum is at the end
        if (s[0] == mn || s[n - 1] == mx) {
            return 1;
        }

        // Minimum or maximum is somewhere in the middle
        for (int i = 1; i < n - 1; i++) {
            if (s[i] == mn || s[i] == mx) {
                return 2;
            }
        }

        // Minimum is at the end and maximum is at the beginning
        return 3;
    }
};