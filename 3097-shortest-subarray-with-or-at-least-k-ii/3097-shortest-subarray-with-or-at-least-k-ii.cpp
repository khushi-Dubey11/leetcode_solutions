class Solution {
public:
    void addBits(vector<int>& bits, int num) {
        for (int i = 0; i < 32; i++) {
            if (num & (1 << i))
                bits[i]++;
        }
    }

    void removeBits(vector<int>& bits, int num) {
        for (int i = 0; i < 32; i++) {
            if (num & (1 << i))
                bits[i]--;
        }
    }

    int getOR(vector<int>& bits) {
        int val = 0;
        for (int i = 0; i < 32; i++) {
            if (bits[i] > 0)
                val |= (1 << i);
        }
        return val;
    }

    int minimumSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> bits(32, 0);

        int ans = INT_MAX;
        int left = 0;

        for (int right = 0; right < n; right++) {
            addBits(bits, nums[right]);

            while (left <= right && getOR(bits) >= k) {
                ans = min(ans, right - left + 1);
                removeBits(bits, nums[left]);
                left++;
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};