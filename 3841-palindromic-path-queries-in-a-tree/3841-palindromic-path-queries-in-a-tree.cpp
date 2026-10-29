class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> parent(n, -1), depth(n, 0), sz(n, 1);
        vector<int> heavy(n, -1), top(n), tin(n), tout(n);
        vector<int> order;
        order.reserve(n);

        // First DFS: parent, depth, subtree size, heavy child
        vector<int> st = {0};
        parent[0] = 0;

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            order.push_back(u);

            for (int v : adj[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                st.push_back(v);
            }
        }

        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];
            int best = 0;

            for (int v : adj[u]) {
                if (parent[v] != u) continue;
                sz[u] += sz[v];

                if (sz[v] > best) {
                    best = sz[v];
                    heavy[u] = v;
                }
            }
        }

        // HLD numbering, keeping every subtree contiguous
        int timer = 0;
        vector<pair<int, int>> todo = {{0, 0}};

        while (!todo.empty()) {
            auto [u, h] = todo.back();
            todo.pop_back();

            for (int x = u; x != -1; x = heavy[x]) {
                top[x] = h;
                tin[x] = ++timer;

                for (int v : adj[x]) {
                    if (parent[v] == x && v != heavy[x])
                        todo.push_back({v, v});
                }
            }
        }

        for (int u = 0; u < n; ++u)
            tout[u] = tin[u] + sz[u] - 1;

        // Binary lifting for LCA
        int LOG = 1;
        while ((1 << LOG) <= n) ++LOG;

        vector<vector<int>> up(LOG, vector<int>(n));
        up[0] = parent;

        for (int j = 1; j < LOG; ++j)
            for (int u = 0; u < n; ++u)
                up[j][u] = up[j - 1][up[j - 1][u]];

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);

            int diff = depth[u] - depth[v];

            for (int j = 0; j < LOG; ++j)
                if (diff & (1 << j))
                    u = up[j][u];

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; --j) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }

            return parent[u];
        };

        // Fenwick tree supporting range XOR updates and point queries
        vector<int> bit(n + 2, 0);

        auto add = [&](int i, int val) {
            for (; i <= n + 1; i += i & -i)
                bit[i] ^= val;
        };

        auto rangeXor = [&](int l, int r, int val) {
            add(l, val);
            add(r + 1, val);
        };

        auto pointQuery = [&](int i) {
            int res = 0;
            for (; i > 0; i -= i & -i)
                res ^= bit[i];
            return res;
        };

        auto mask = [](char c) {
            return 1 << (c - 'a');
        };

        // Store each node's character mask over its subtree range
        for (int u = 0; u < n; ++u)
            rangeXor(tin[u], tout[u], mask(s[u]));

        vector<bool> answer;

        for (string& q : queries) {
            string op;
            int u;
            char c;

            stringstream ss(q);
            ss >> op >> u;

            if (op == "update") {
                ss >> c;

                int delta = mask(s[u]) ^ mask(c);
                rangeXor(tin[u], tout[u], delta);
                s[u] = c;
            } else {
                int v;
                ss >> v;

                int w = lca(u, v);

                int pathMask = pointQuery(tin[u])
                             ^ pointQuery(tin[v])
                             ^ mask(s[w]);

                // A palindrome permutation allows at most one odd frequency
                answer.push_back(
                    (pathMask & (pathMask - 1)) == 0
                );
            }
        }

        return answer;
    }
};