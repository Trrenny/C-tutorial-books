class Solution {
public:
    bool isValid(string s) {
        std::unordered_map<char, int> matcher_{
			{'(',1},
			{'[',2},
			{'{',3},
            {')',4},
			{']',5},
			{'}',6}};
        std::stack<int> st;
        for(auto i : s)
        {
            if(matcher_[i] >= 1 && matcher_[i] <= 3)
            {
                st.push(matcher_[i]);
            }
            else if( !st.empty() && matcher_[i] > 3 && st.top() == matcher_[i] - 3 )
            {
                st.pop();
            }
            else
            {
                return false;
            }
        }
        if(st.empty())
            return true;
        else
        {
                return false;
        }

    }
};