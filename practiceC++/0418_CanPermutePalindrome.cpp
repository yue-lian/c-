#include<iostream>
#include <vector>

class Solution {
public:
    bool canPermutePalindrome(std::string s) {

        std::vector<int> table(s.size(), 0);

        for (auto& ch : s) {
            table[ch]++;
        }
        bool x = s.size() % 2 == 1;
        int temp = 0;
        for (int i = 0; i < table.size();i++ ) {
            if ((table[i] % 2 == 1) && x)
            {
                temp += 1;
            }
            if ((table[i] % 2 != 1) && !x)
            {
                temp += 1;
            }
        }
        if (temp == 1 && x)
        {
            return true;
        }
        else if (temp != 1 && !x)
        {
            return true;
        }
        else {
            return false;
        }

    }
};

int main() {
    Solution sol;
    std::cout << sol.canPermutePalindrome("asdfdfsa");
}