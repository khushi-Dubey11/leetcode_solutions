class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();

        vector<vector<pair<int,int>>> graph(n);
        vector<int> indegree(n);

        int mx = 0;
        for (auto &e : edges) {
            graph[e[0]].push_back({e[1], e[2]});
            indegree[e[1]]++;
            mx = max(mx, e[2]);
        }

        // Topological order
        vector<int> topo;
        queue<int> q;
        vector<int> deg = indegree;

        for (int i = 0; i < n; i++)
            if (deg[i] == 0)
                q.push(i);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.push_back(u);

            for (auto &[v, w] : graph[u]) {
                if (--deg[v] == 0)
                    q.push(v);
            }
        }

        auto check = [&](int limit) {
            const long long INF = 4e18;
            vector<long long> dp(n, INF);
            dp[0] = 0;

            for (int u : topo) {
                if (dp[u] == INF)
                    continue;

                if (u != 0 && u != n - 1 && !online[u])
                    continue;

                for (auto &[v, w] : graph[u]) {
                    if (w < limit)
                        continue;

                    if (v != n - 1 && !online[v])
                        continue;

                    dp[v] = min(dp[v], dp[u] + w);
                }
            }

            return dp[n - 1] <= k;
        };

        int lo = 0, hi = mx, ans = -1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            if (check(mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return ans;
    }
};