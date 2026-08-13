class Solution {
    struct Node {
        int max_len;
        int pref_len;
        int suff_len;
        char pref_char;
        char suff_char;
        int len;
    };

    vector<Node> tree;

    void pull(int node) {
        int left = 2 * node + 1;
        int right = 2 * node + 2;
        tree[node].len = tree[left].len + tree[right].len;
        tree[node].pref_char = tree[left].pref_char;
        tree[node].suff_char = tree[right].suff_char;
        
        tree[node].pref_len = tree[left].pref_len;
        if (tree[left].pref_len == tree[left].len && tree[left].pref_char == tree[right].pref_char) {
            tree[node].pref_len += tree[right].pref_len;
        }
        
        tree[node].suff_len = tree[right].suff_len;
        if (tree[right].suff_len == tree[right].len && tree[right].suff_char == tree[left].suff_char) {
            tree[node].suff_len += tree[left].suff_len;
        }
        
        tree[node].max_len = max(tree[left].max_len, tree[right].max_len);
        if (tree[left].suff_char == tree[right].pref_char) {
            tree[node].max_len = max(tree[node].max_len, tree[left].suff_len + tree[right].pref_len);
        }
    }

    void build(int node, int start, int end, const string& s) {
        if (start == end) {
            tree[node].len = 1;
            tree[node].max_len = 1;
            tree[node].pref_len = 1;
            tree[node].suff_len = 1;
            tree[node].pref_char = s[start];
            tree[node].suff_char = s[start];
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node + 1, start, mid, s);
        build(2 * node + 2, mid + 1, end, s);
        pull(node);
    }

    void update(int node, int start, int end, int idx, char c) {
        if (start == end) {
            tree[node].pref_char = c;
            tree[node].suff_char = c;
            return;
        }
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node + 1, start, mid, idx, c);
        } else {
            update(2 * node + 2, mid + 1, end, idx, c);
        }
        pull(node);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.length();
        tree.resize(4 * n);
        build(0, 0, n - 1, s);
        
        int k = queryIndices.size();
        vector<int> ans(k);
        for (int i = 0; i < k; ++i) {
            update(0, 0, n - 1, queryIndices[i], queryCharacters[i]);
            ans[i] = tree[0].max_len;
        }
        return ans;
    }
};