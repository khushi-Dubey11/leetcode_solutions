class Solution {
public:
    static constexpr int MOD = 1'000'000'007;

    vector<int> sumAndMultiply(vector<int>& digits,
                              vector<long long>& pref,
                              vector<long long>& pw,
                              int l, int r) {
        return {};
    }

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();

        vector<int> pos;
        vector<int> d;

        for (int i = 0; i < n; i++) {
            if (s[i] != '0') {
                pos.push_back(i);
                d.push_back(s[i] - '0');
            }
        }

        int m = d.size();

        vector<long long> prefNum(m + 1, 0);
        vector<long long> prefSum(m + 1, 0);
        vector<long long> pw(m + 1, 1);

        for (int i = 1; i <= m; i++)
            pw[i] = pw[i - 1] * 10 % MOD;

        for (int i = 0; i < m; i++) {
            prefNum[i + 1] = (prefNum[i] * 10 + d[i]) % MOD;
            prefSum[i + 1] = prefSum[i] + d[i];
        }

        vector<int> ans;

        for (auto &q : queries) {
            int l = lower_bound(pos.begin(), pos.end(), q[0]) - pos.begin();
            int r = upper_bound(pos.begin(), pos.end(), q[1]) - pos.begin() - 1;

            if (l > r) {
                ans.push_back(0);
                continue;
            }

            int len = r - l + 1;

            long long x =
                (prefNum[r + 1] -
                 prefNum[l] * pw[len] % MOD +
                 MOD) % MOD;

            long long sum = prefSum[r + 1] - prefSum[l];

            ans.push_back(x * sum % MOD);
        }

        return ans;
    }
};