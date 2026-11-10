class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;

        int leftMax = 0;
        int rightMax = 0;

        int totalWater = 0;

        while(left < right){
            if(height[left] <= height[right]){
                leftMax = max(height[left], leftMax);
                totalWater += leftMax - height[left];
                left++;
            }
            else{
                rightMax = max(height[right], rightMax);
                totalWater += rightMax - height[right];
                right--;
            }
        }

        return totalWater;
    }
};