/*
 * Problem: LeetCode 1344 - Angle Between Hands of a Clock
 * Link: https://leetcode.com
 * 
 * Time Complexity:  O(1) - Evaluates using simple mathematical equations in constant time.
 * Space Complexity: O(1) - Constant auxiliary space with no memory allocations.
 * 
 * Approach:
 * Solved using absolute angular positioning relative to the 12 o'clock position (0°):
 * 1. Minute Hand: Moves 360° in 60 minutes, which equals 6° per minute.
 * 2. Hour Hand: Moves 360° in 12 hours (30° per hour), plus an additional 0.5° 
 *    per minute as it drifts smoothly between hour marks.
 * 3. Calculation: Takes the absolute difference between both absolute angles and returns 
 *    the minimal interior angle by checking the complement angle (360° - angle).
 */
class Solution {
public:
    double angleClock(int hour, int minutes) {
     double hourAngle = 30*(hour % 12) + 0.5 * minutes;
     double minuteAngle = 6 * minutes ; 
     double angle = abs( hourAngle - minuteAngle);
     return min( angle , 360 - angle);
    }
};