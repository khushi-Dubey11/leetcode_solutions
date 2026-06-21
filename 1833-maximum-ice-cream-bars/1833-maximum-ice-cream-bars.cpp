class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        sort(costs.begin() , costs.end());
        int count = 0;
        for(int cost : costs) {
            if (coins < cost) 
            break;
            coins = coins - cost;
            count = count + 1;
        }
        return count;
    }
};