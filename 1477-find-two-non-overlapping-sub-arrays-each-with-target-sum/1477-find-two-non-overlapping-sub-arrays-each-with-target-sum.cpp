class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {

        int n = arr.size();

        const int INF = 1e9;

        // best[i] = minimum length of a target-sum
        // subarray ending at or before i
        vector<int> best(n, INF);

        int left = 0;
        int sum = 0;
        int ans = INF;

        for (int right = 0; right < n; right++) {

            sum += arr[right];

            // Shrink window if sum is too large
            while (sum > target) {
                sum -= arr[left];
                left++;
            }

            // If current window has target sum
            if (sum == target) {

                int len = right - left + 1;

                // Check if there is a previous
                // non-overlapping subarray
                if (left > 0 && best[left - 1] != INF) {
                    ans = min(ans, best[left - 1] + len);
                }
            }

            // Update best for current position
            if (right == 0) {
                best[right] =
                    (sum == target ? right - left + 1 : INF);
            }
            else {
                best[right] = best[right - 1];

                if (sum == target) {
                    best[right] =
                        min(best[right],
                            right - left + 1);
                }
            }
        }

        return ans == INF ? -1 : ans;
    }
};