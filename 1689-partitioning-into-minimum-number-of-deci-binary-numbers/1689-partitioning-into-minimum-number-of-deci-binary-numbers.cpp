class Solution {
public:
    int minPartitions(string n) {
        int maximum = 0;

        for (char ch : n) {
            maximum = max(maximum, ch - '0');
        }

        return maximum;
    }
};