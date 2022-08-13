class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        if (nums.size() < 3) return ans;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) return ans;
            // 去重
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right) {
                if (nums[left] + nums[right] + nums[i] > 0) {
                    right--;
                } else if (nums[left] + nums[right] + nums[i] < 0){
                    left++;
                } else {
                    ans.push_back({nums[left], nums[right], nums[i]});
                    while (right > left && nums[right] == nums[right - 1]) right--;
                    while (right > left && nums[left] == nums[left + 1]) left++;
                    left++;
                    right--;
                }
            }
        }
        return ans;
    }
};