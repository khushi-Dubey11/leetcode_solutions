class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1,
                       vector<vector<int>>& img2) {

        int n = img1.size();

        vector<pair<int, int>> ones1;
        vector<pair<int, int>> ones2;

        // Store coordinates of 1s
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (img1[i][j] == 1)
                    ones1.push_back({i, j});

                if (img2[i][j] == 1)
                    ones2.push_back({i, j});
            }
        }

        unordered_map<int, int> count;

        int ans = 0;

        // Compare every 1 from img1 with every 1 from img2
        for (auto [x1, y1] : ones1) {

            for (auto [x2, y2] : ones2) {

                int dx = x2 - x1;
                int dy = y2 - y1;

                // Encode (dx, dy) into one integer
                int key = dx * 100 + dy;

                count[key]++;

                ans = max(ans, count[key]);
            }
        }

        return ans;
    }
};