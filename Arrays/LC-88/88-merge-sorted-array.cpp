
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        
        int length = m + n;

        for(int i = m; i < length; i++){
            nums1[i] = nums2[i - m];
            cout << nums1[i];
        }

        sort(nums1.begin(), nums1.end());
    }
};