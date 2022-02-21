class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        std::vector<char> result;
        std::vector<char>::iterator iterator1 = result.begin();
        int num{0};
        if (s.size() != 0 && s.size() != 1 )
        {
            for (int i = 0 ; i < s.size();++i)
            {
                
                if(find(result.begin(),result.end(),s[i]) == result.end())
                {
                    result.push_back(s[i]);
				    if(num < result.size())
					    num = result.size();
                }

                else
                {
                    
                    iterator1= find(result.begin(),result.end(),s[i]);
                    result.erase(result.begin(),++iterator1);
                    result.push_back(s[i]);
                    if(num < result.size())
                        num = result.size();
                }
            }

            return num;
        }

        else if(s.size() == 0)
            return 0;
        else
            return 1;

    }
};