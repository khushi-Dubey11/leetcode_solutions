/*
Approach
The biker starts at altitude 0. As we traverse the 'gain' array, we continuously 
update the current altitude by adding each gain value. At every step, we keep 
track of the maximum altitude reached so far. Since we only need the current 
altitude and the highest altitude encountered, two variables are sufficient.

 Algorithm
1. Initialize curr = 0 and maxAltitude = 0.
2. Iterate through each value 'g' in gain:
   - Update the current altitude: curr += g.
   - Update the maximum altitude: maxAltitude = max(maxAltitude, curr).
3. Return maxAltitude.

 Complexity
- Time Complexity: O(n) — Where n is the length of the 'gain' array. 
                    
- Space Complexity: O(1) — Constant extra space used as we only maintain 
                     two variables.
*/
class Solution {
public:
    int largestAltitude(vector<int>& gain) {
      int curr = 0;
      int ans = 0;
      for( int x : gain) {
        curr = curr + x;
        ans = max(ans , curr);
      }
      return ans;
    }
};