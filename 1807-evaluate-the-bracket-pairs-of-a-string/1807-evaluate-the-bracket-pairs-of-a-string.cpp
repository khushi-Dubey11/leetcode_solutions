class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {

        unordered_map<string, string> mp;

        // Store key-value pairs
        for (auto &pair : knowledge) {
            mp[pair[0]] = pair[1];
        }

        string ans;

        for (int i = 0; i < s.size(); i++) {

            // Found '('
            if (s[i] == '(') {

                int j = i + 1;

                // Find ')'
                while (s[j] != ')') {
                    j++;
                }

                // Extract key
                string key = s.substr(i + 1, j - i - 1);

                // Check if key exists
                if (mp.count(key)) {
                    ans += mp[key];
                } else {
                    ans += "?";
                }

                // Skip to character after ')'
                i = j;
            }

            // Normal character
            else {
                ans += s[i];
            }
        }

        return ans;
    }
};