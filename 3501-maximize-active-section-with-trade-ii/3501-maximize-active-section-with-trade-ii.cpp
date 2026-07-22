struct Block {
    int start, end, len;
};

class SegmentTree {
    int n;
    vector<int> tree;
    
    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = start + (end - start) / 2;
        return max(query(2 * node, start, mid, l, r),
                   query(2 * node + 1, mid + 1, end, l, r));
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        if (n > 0) {
            tree.resize(4 * n, 0);
            build(arr, 1, 0, n - 1);
        }
    }

    int rangeMax(int l, int r) {
        if (l > r || n == 0) return 0;
        return query(1, 0, n - 1, l, r);
    }
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int total_ones = 0;
        for (char c : s) if (c == '1') total_ones++;

        // 1. Group contiguous blocks of '0's
        vector<Block> blocks;
        for (int i = 0; i < n; ) {
            if (s[i] == '0') {
                int start = i;
                while (i < n && s[i] == '0') i++;
                blocks.push_back({start, i - 1, i - start});
            } else {
                i++;
            }
        }

        int m = blocks.size();
        if (m < 2) {
            // If fewer than 2 zero-blocks exist globally, no pairs can be merged
            return vector<int>(queries.size(), total_ones);
        }

        // 2. Precompute sums of adjacent zero-block lengths
        vector<int> pairSums(m - 1, 0);
        for (int i = 0; i < m - 1; i++) {
            pairSums[i] = blocks[i].len + blocks[i + 1].len;
        }

        SegmentTree stPair(pairSums);
        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int ql = q[0], qr = q[1];

            // Binary search: First block overlapping the query window (end >= ql)
            int first_idx = -1;
            int low = 0, high = m - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (blocks[mid].end >= ql) {
                    first_idx = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            // Binary search: Last block overlapping the query window (start <= qr)
            int last_idx = -1;
            low = 0, high = m - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (blocks[mid].start <= qr) {
                    last_idx = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            // If less than 2 blocks overlap inside the window, no trade is valid
            if (first_idx == -1 || last_idx == -1 || first_idx >= last_idx) {
                ans.push_back(total_ones);
                continue;
            }

            int max_gain = 0;

            // Calculate truncated lengths for boundary blocks
            int len_first = blocks[first_idx].end - max(ql, blocks[first_idx].start) + 1;
            int len_last = min(qr, blocks[last_idx].end) - blocks[last_idx].start + 1;

            // Case A: Exactly two blocks overlap the window
            if (last_idx == first_idx + 1) {
                max_gain = len_first + len_last;
            } 
            // Case B: More than two blocks overlap the window
            else {
                // Pair 1: First block (truncated) + Second block (full)
                max_gain = max(max_gain, len_first + blocks[first_idx + 1].len);
                
                // Pair 2: Penultimate block (full) + Last block (truncated)
                max_gain = max(max_gain, blocks[last_idx - 1].len + len_last);
                
                // Internal Pairs: Fully enclosed un-truncated adjacent pairs
                if (first_idx + 1 <= last_idx - 2) {
                    max_gain = max(max_gain, stPair.rangeMax(first_idx + 1, last_idx - 2));
                }
            }

            ans.push_back(total_ones + max_gain);
        }

        return ans;
    }
};
