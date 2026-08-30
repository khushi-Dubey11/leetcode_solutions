class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        int mn = min_element(nums.begin(), nums.end()) - nums.begin();
        int mx = max_element(nums.begin(), nums.end()) - nums.begin();

        int a = min(mn, mx);
        int b = max(mn, mx);

        return min({
            b + 1,              // both from left
            n - a,              // both from right
            a + 1 + n - b       // one from each side
        });
    }
};