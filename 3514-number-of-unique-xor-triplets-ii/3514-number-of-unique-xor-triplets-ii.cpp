class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();

        if (n == 1)
            return 1;

        unordered_set<int> pairXor;

        // Store all XORs of distinct pairs
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                pairXor.insert(nums[i] ^ nums[j]);
            }
        }

        vector<bool> seen(2048, false);

        // Triplets with all three indices equal
        for (int x : nums)
            seen[x] = true;

        // Pair XOR combined with any element
        for (int px : pairXor) {
            for (int x : nums) {
                seen[px ^ x] = true;
            }
        }

        int ans = 0;
        for (bool v : seen)
            ans += v;

        return ans;
    }
};