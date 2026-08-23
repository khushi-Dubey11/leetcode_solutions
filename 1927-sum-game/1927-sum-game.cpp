class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();

        int leftSum = 0, rightSum = 0;
        int leftQ = 0, rightQ = 0;

        // First half
        for (int i = 0; i < n / 2; i++) {
            if (num[i] == '?')
                leftQ++;
            else
                leftSum += num[i] - '0';
        }

        // Second half
        for (int i = n / 2; i < n; i++) {
            if (num[i] == '?')
                rightQ++;
            else
                rightSum += num[i] - '0';
        }

        // Odd number of '?' -> Alice always wins
        if ((leftQ + rightQ) % 2 == 1)
            return true;

        // Bob can force equality only in this exact case
        return leftSum - rightSum != 9 * (rightQ - leftQ) / 2;
    }
};