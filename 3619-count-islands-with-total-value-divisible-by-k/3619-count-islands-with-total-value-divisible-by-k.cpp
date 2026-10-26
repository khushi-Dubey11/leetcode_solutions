class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;

        vector<int> dirs = {-1, 0, 1, 0, -1};

        auto dfs = [&](this auto&& dfs, int i, int j) -> long long {
            long long sum = grid[i][j];
            grid[i][j] = 0; // Mark visited

            for (int d = 0; d < 4; d++) {
                int x = i + dirs[d];
                int y = j + dirs[d + 1];

                if (x >= 0 && x < m &&
                    y >= 0 && y < n &&
                    grid[x][y] > 0) {
                    sum += dfs(x, y);
                }
            }

            return sum;
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0) {
                    long long sum = dfs(i, j);

                    if (sum % k == 0) {
                        ans++;
                    }
                }
            }
        }

        return ans;
    }
};