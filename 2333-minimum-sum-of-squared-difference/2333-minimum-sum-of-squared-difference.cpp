class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1,
                               vector<int>& nums2,
                               int k1, int k2) {

        int n = nums1.size();
        long long k = (long long)k1 + k2;

        vector<int> diff(n);
        long long sum = 0;
        int mx = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            sum += diff[i];
            mx = max(mx, diff[i]);
        }

        if (sum <= k)
            return 0;

        int low = 0, high = mx;

        while (low < high) {
            int mid = low + (high - low) / 2;

            long long operations = 0;

            for (int d : diff) {
                if (d > mid)
                    operations += d - mid;
            }

            if (operations <= k)
                high = mid;
            else
                low = mid + 1;
        }

        int limit = low;

        for (int& d : diff) {
            if (d > limit) {
                k -= d - limit;
                d = limit;
            }
        }

        long long ans = 0;

        for (int d : diff) {
            if (d == limit && k > 0) {
                d--;
                k--;
            }

            ans += 1LL * d * d;
        }

        return ans;
    }
};