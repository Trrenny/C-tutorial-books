class Solution {
public:
    int maxArea(vector<int>& height) {

        int max_area{0};
        int min_b{0};
        if (height.size() == 2)
        {
            return (height[0] > height[1]?height[1]:height[0]);
        }

        int i = 0;
        int j = height.size() - 1;

        for(;i< j;i++)
        {
            min_b = height[i] < height[j] ? height[i]:height[j];
            if(max_area < min_b * (j-i))
            {
                max_area = min_b * (j-i);
            }
            if(height[i] < height[j])
            {
                continue;
            }

            else
            {
                j -=1;
                i -=1;
            }
        }

        return max_area;
            

    }
};