class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
     vector<int> ans;
     for (int p : nums) {
        if(p == 2) {
            ans.push_back(-1);
            continue;
        }
        int t = 0;
        while (( p >> t) & 1)
        t++;
        ans.push_back(p ^ (1 << (t - 1)));
     } 
     return ans;
    }
};