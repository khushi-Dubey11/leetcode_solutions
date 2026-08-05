class Solution {
public:
    void dfs(int node, vector<vector<int>>& graph, vector<int>& vis) {
        vis[node] = 1;
        for (int nxt : graph[node]) {
            if (!vis[nxt])
                dfs(nxt, graph, vis);
        }
    }

    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);

        for (auto &e : invocations)
            graph[e[0]].push_back(e[1]);

        vector<int> suspicious(n, 0);
        dfs(k, graph, suspicious);

        // If any safe method invokes a suspicious method,
        // then no methods can be removed.
        for (auto &e : invocations) {
            int u = e[0], v = e[1];
            if (!suspicious[u] && suspicious[v]) {
                vector<int> ans;
                for (int i = 0; i < n; i++)
                    ans.push_back(i);
                return ans;
            }
        }

        // Return remaining (safe) methods
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i])
                ans.push_back(i);
        }
        return ans;
    }
};