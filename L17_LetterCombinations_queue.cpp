class Solution {
private:
    std::unordered_map<char, string> map_{
        {'1', ""},
        {'2', "abc"},
        {'3', "def"},
        {'4' , "ghi"},
        {'6' ,"mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"},
        {'5', "jkl"}
    };
    std::queue<string> que_;
    std::vector<string> res_;
public:

    vector<string> letterCombinations(string digits) 
    {
        for (int i = 0; i < digits.size(); i++)
        {
            string s;
            s = map_[digits[i]];
            int num = que_.size();
            if(num == 0)
            {
                
                for(auto c : s)
                {
                    string  bb = "a";
                    bb[0] = c;
                    que_.push(bb);
                }
                continue;
            }
            for(int j = 0 ; j < num ; j++)
            {  
                string s_front = que_.front();
                que_.pop();
                string s_after;
                for(auto c : s)
                {                   
                    s_after = s_front + c;
                    que_.push(s_after);
                }
            }
        }

        for(int i=que_.size();i>0;i--)
        { //一定要注意队列的遍历啊！！！
            res_.push_back(que_.front());
            que_.pop();
        }
        return res_;
    }
    
};