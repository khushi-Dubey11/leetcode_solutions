class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival,
                               vector<int>& load) {

        vector<int> count(k, 0);

        set<int> free;

        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> busy;

        // Initially all servers are available
        for (int i = 0; i < k; i++) {
            free.insert(i);
        }

        for (int i = 0; i < arrival.size(); i++) {

            int time = arrival[i];

            // Release servers that have finished
            while (!busy.empty() && busy.top().first <= time) {
                free.insert(busy.top().second);
                busy.pop();
            }

            // All servers are busy
            if (free.empty()) {
                continue;
            }

            // Preferred server
            int preferred = i % k;

            // Find next available server
            auto it = free.lower_bound(preferred);

            // Circular wrap-around
            if (it == free.end()) {
                it = free.begin();
            }

            int server = *it;

            free.erase(it);

            // Update request count
            count[server]++;

            // Mark server as busy
            busy.push({time + load[i], server});
        }

        // Find maximum requests handled
        int maxi = *max_element(count.begin(), count.end());

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};