class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> st;
        string current = "";

        for (char c : s) {

            // Opening parenthesis
            if (c == '(') {
                st.push(current);
                current = "";
            }

            // Closing parenthesis
            else if (c == ')') {
                reverse(current.begin(), current.end());

                current = st.top() + current;
                st.pop();
            }

            // Normal character
            else {
                current += c;
            }
        }

        return current;
    }
};