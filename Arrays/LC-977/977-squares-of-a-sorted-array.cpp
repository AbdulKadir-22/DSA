class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> square(nums.size());

        for(int i = 0;i< nums.size(); i++){
            square[i] = nums[i] * nums[i];
        }

        sort(square.begin(),square.end());

        return square;
    }
};