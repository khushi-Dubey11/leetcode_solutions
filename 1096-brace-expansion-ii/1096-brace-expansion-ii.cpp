class Solution {
public:

    string s;
    int pos;

    // Cartesian product / concatenation
    set<string> multiply(set<string>& A, set<string>& B) {
        set<string> result;

        for (string a : A) {
            for (string b : B) {
                result.insert(a + b);
            }
        }

        return result;
    }

    set<string> parse() {

        set<string> result;
        set<string> current = {""};

        while (pos < s.size() && s[pos] != '}') {

            // Comma -> finish current term
            if (s[pos] == ',') {

                for (string str : current) {
                    result.insert(str);
                }

                current = {""};
                pos++;
            }

            // Opening brace -> recursively parse it
            else if (s[pos] == '{') {

                pos++; // skip '{'

                set<string> inside = parse();

                pos++; // skip '}'

                current = multiply(current, inside);
            }

            // Normal character
            else {

                string ch(1, s[pos]);

                set<string> single = {ch};

                current = multiply(current, single);

                pos++;
            }
        }

        // Add the final term
        for (string str : current) {
            result.insert(str);
        }

        return result;
    }

    vector<string> braceExpansionII(string expression) {

        s = expression;
        pos = 0;

        set<string> ans = parse();

        return vector<string>(ans.begin(), ans.end());
    }
};