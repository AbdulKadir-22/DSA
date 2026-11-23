class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string lcp = strs[0];

        for (int i = 0; i < lcp.size(); i++) {
            for (int j = 1; j < strs.size(); j++) {

                if (i >= strs[j].size() ||
                    lcp[i] != strs[j][i]) {
                    return lcp.substr(0, i);
                }

            }
        }

        return lcp;
    }
};