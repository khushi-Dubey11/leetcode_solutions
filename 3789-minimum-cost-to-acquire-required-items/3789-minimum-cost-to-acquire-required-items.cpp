class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {

        long long case1 = 1LL * need1 * cost1
                        + 1LL * need2 * cost2;

        int mn = min(need1, need2);
        int mx = max(need1, need2);

        long long case2 = 1LL * mn * costBoth
                        + 1LL * (need1 - mn) * cost1
                        + 1LL * (need2 - mn) * cost2;

        long long case3 = 1LL * mx * costBoth;

        return min({case1, case2, case3});
    }
};