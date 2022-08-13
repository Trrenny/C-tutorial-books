class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int clo = 1000;
        int res;
        for(int i = 0 ; i < nums.size()-2; i++)
        {
            
            int left = i+1;
            int right = nums.size() -1;
            while((left < right))
            {
             int sum = nums[i] + nums[left] + nums[right];
                if(fabs(sum - target) < fabs(res - target))
                    res = sum;
                if(sum > target){
                    right--;
                }
                else{
                    left++;
                }
            }
            

        }

        return res;