/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
      int first = -1;
        int prevCritical = -1;
        int minDist = INT_MAX;

        int index = 1;

        ListNode* prev = head;
        ListNode* curr = head->next;

        while (curr->next != nullptr) {

            bool critical =
                (curr->val > prev->val && curr->val > curr->next->val) ||
                (curr->val < prev->val && curr->val < curr->next->val);

            if (critical) {

                // First critical point
                if (first == -1) {
                    first = index;
                }

                // Distance from previous critical point
                if (prevCritical != -1) {
                    minDist = min(minDist, index - prevCritical);
                }

                prevCritical = index;
            }

            prev = curr;
            curr = curr->next;
            index++;
        }

        // Less than 2 critical points
        if (minDist == INT_MAX) {
            return {-1, -1};
        }

        // Distance between first and last critical point
        int maxDist = prevCritical - first;

        return {minDist, maxDist};
    }
};