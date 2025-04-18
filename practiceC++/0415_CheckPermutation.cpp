#include<iostream>
#include <vector>
/*
* 2500415
给定两个由小写字母组成的字符串 s1 和 s2，请编写一个程序，确定其中一个字符串的字符重新排列后，能否变成另一个字符串。

示例 1：

输入: s1 = "abc", s2 = "bca"
输出: true 
示例 2：

输入: s1 = "abc", s2 = "bad"
输出: false
说明：

0 <= len(s1) <= 100 
0 <= len(s2) <= 100 
*/
class Solution {
public:
    bool CheckPermutation(std::string s1, std::string s2) {
		if (s1.size() != s2.size())
		{
			return false;
		}
		std::vector<int> table(128, 0);

		for (auto& ch : s1) {
			table[ch]++;
		}
		for (auto& ch : s2) {
			table[ch]--;
			if (table[ch] < 0)
			{
				return false;
			}
		}
		return true;
	}
};

//int main() {
//	Solution sol;
//	std::string s1 = "ABCD";
//	std::string s2 = "ABCD";
//	std::cout << std::boolalpha << sol.CheckPermutation(s1,s2) << std::endl;
//}
