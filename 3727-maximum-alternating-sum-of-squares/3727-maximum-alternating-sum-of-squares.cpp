class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();

        for (int &x : nums) {
            x = x * x;
        }

        sort(nums.begin(), nums.end());

        long long ans = 0;

        for (int i = 0; i < n; i++) {
            if (i < n / 2)
                ans -= nums[i];
            else
                ans += nums[i];
        }

        return ans;
    }
};