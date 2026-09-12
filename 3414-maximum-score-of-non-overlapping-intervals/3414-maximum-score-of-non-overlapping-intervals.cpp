class Solution {
public:

    struct Result {
        long long weight;
        vector<int> indices;
    };

    vector<vector<Result>> memo;
    vector<vector<int>> a;
    vector<int> starts;
    int n;

    Result better(Result x, Result y) {
        if (x.weight != y.weight)
            return x.weight > y.weight ? x : y;

        return lexicographical_compare(
            x.indices.begin(), x.indices.end(),
            y.indices.begin(), y.indices.end()
        ) ? x : y;
    }

    Result dp(int i, int k) {

        if (i == n || k == 0)
            return {0, {}};

        if (memo[i][k].weight != -1)
            return memo[i][k];

        // Don't take current interval
        Result skip = dp(i + 1, k);

        // Take current interval
        int next = upper_bound(
            starts.begin() + i + 1,
            starts.end(),
            a[i][1]
        ) - starts.begin();

        Result take = dp(next, k - 1);

        take.weight += a[i][2];
        take.indices.push_back(a[i][3]);

        sort(take.indices.begin(), take.indices.end());

        memo[i][k] = better(skip, take);

        return memo[i][k];
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {

        n = intervals.size();

        a.clear();

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by starting point
        sort(a.begin(), a.end());

        starts.resize(n);

        for (int i = 0; i < n; i++)
            starts[i] = a[i][0];

        memo.assign(n, vector<Result>(5, {-1, {}}));

        return dp(0, 4).indices;
    }
};