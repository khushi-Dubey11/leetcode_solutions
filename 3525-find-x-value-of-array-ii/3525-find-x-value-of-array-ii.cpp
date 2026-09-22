class Solution {
public:

    struct Node {
        int prod;
        int cnt[5];

        Node() {
            prod = 1;
            for (int i = 0; i < 5; i++)
                cnt[i] = 0;
        }
    };

    int k;
    vector<Node> tree;

    // Merge two segments: left + right
    Node merge(Node left, Node right) {

        Node res;

        // Product of the complete segment
        res.prod = (left.prod * right.prod) % k;

        // Prefixes completely inside left
        for (int r = 0; r < k; r++) {
            res.cnt[r] = left.cnt[r];
        }

        // Prefixes that enter the right segment
        for (int r = 0; r < k; r++) {
            int newRemainder = (left.prod * r) % k;
            res.cnt[newRemainder] += right.cnt[r];
        }

        return res;
    }

    // Build segment tree
    void build(vector<int>& nums, int node, int l, int r) {

        if (l == r) {
            int rem = nums[l] % k;

            tree[node].prod = rem;
            tree[node].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) / 2;

        build(nums, node * 2, l, mid);
        build(nums, node * 2 + 1, mid + 1, r);

        tree[node] = merge(tree[node * 2],
                           tree[node * 2 + 1]);
    }

    // Point update
    void update(int node, int l, int r, int index, int value) {

        if (l == r) {
            int rem = value % k;

            tree[node] = Node();

            tree[node].prod = rem;
            tree[node].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (index <= mid)
            update(node * 2, l, mid, index, value);
        else
            update(node * 2 + 1, mid + 1, r, index, value);

        tree[node] = merge(tree[node * 2],
                           tree[node * 2 + 1]);
    }

    // Range query
    Node query(int node, int l, int r, int ql, int qr) {

        // Completely inside range
        if (ql <= l && r <= qr)
            return tree[node];

        int mid = (l + r) / 2;

        // Entire query is in left
        if (qr <= mid)
            return query(node * 2, l, mid, ql, qr);

        // Entire query is in right
        if (ql > mid)
            return query(node * 2 + 1, mid + 1, r, ql, qr);

        // Query overlaps both sides
        Node leftPart =
            query(node * 2, l, mid, ql, qr);

        Node rightPart =
            query(node * 2 + 1, mid + 1, r, ql, qr);

        return merge(leftPart, rightPart);
    }

    vector<int> resultArray(vector<int>& nums,
                            int K,
                            vector<vector<int>>& queries) {

        k = K;

        int n = nums.size();

        tree.resize(4 * n);

        build(nums, 1, 0, n - 1);

        vector<int> answer;

        for (auto &q : queries) {

            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Permanent update
            update(1, 0, n - 1, index, value);

            // Query nums[start ... n-1]
            Node res = query(1, 0, n - 1,
                             start, n - 1);

            answer.push_back(res.cnt[x]);
        }

        return answer;
    }
};