class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size(), n = classroom[0].size();

        int sr = 0, sc = 0, cnt = 0;

        // Assign an index to every litter
        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }
                else if (classroom[i][j] == 'L') {
                    id[i][j] = cnt++;
                }
            }
        }

        if (cnt == 0) return 0;

        int fullMask = (1 << cnt) - 1;

        queue<array<int, 4>> q;

        // r, c, energy, mask
        q.push({sr, sc, energy, fullMask});

        // visited[r][c][energy][mask]
        vector<vector<vector<vector<bool>>>> vis(
            m,
            vector<vector<vector<bool>>>(
                n,
                vector<vector<bool>>(energy + 1,
                    vector<bool>(1 << cnt, false)
                )
            )
        );

        vis[sr][sc][energy][fullMask] = true;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        int moves = 0;

        while (!q.empty()) {

            int sz = q.size();

            while (sz--) {

                auto [r, c, en, mask] = q.front();
                q.pop();

                if (mask == 0)
                    return moves;

                if (en == 0)
                    continue;

                for (int k = 0; k < 4; k++) {

                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    if (nr < 0 || nr >= m ||
                        nc < 0 || nc >= n ||
                        classroom[nr][nc] == 'X')
                        continue;

                    int nen = en - 1;
                    int nmask = mask;

                    // Recharge
                    if (classroom[nr][nc] == 'R')
                        nen = energy;

                    // Collect litter
                    if (classroom[nr][nc] == 'L') {
                        int bit = id[nr][nc];
                        nmask &= ~(1 << bit);
                    }

                    if (!vis[nr][nc][nen][nmask]) {
                        vis[nr][nc][nen][nmask] = true;
                        q.push({nr, nc, nen, nmask});
                    }
                }
            }

            moves++;
        }

        return -1;
    }
};