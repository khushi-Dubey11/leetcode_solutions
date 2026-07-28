class Solution {
public:
    string smallestPalindrome(string s) {
        int freq[26] = {0};

        // Count frequency of each character
        for (char ch : s) {
            freq[ch - 'a']++;
        }

        string firstHalf = "";
        char middle = '\0';

        // Build the smallest first half
        for (char ch = 'a'; ch <= 'z'; ch++) {
            int count = freq[ch - 'a'];

            // Add half of the occurrences
            firstHalf += string(count / 2, ch);

            // Odd character goes in the middle
            if (count % 2 == 1) {
                middle = ch;
            }
        }

        string answer = firstHalf;

        // Add middle character if present
        if (middle != '\0') {
            answer += middle;
        }

        // Add reverse of first half
        reverse(firstHalf.begin(), firstHalf.end());
        answer += firstHalf;

        return answer;
    }
};