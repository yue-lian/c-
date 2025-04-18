#include<iostream>
#include <vector>
/*
* 2500415
����������Сд��ĸ��ɵ��ַ��� s1 �� s2�����дһ������ȷ������һ���ַ������ַ��������к��ܷ�����һ���ַ�����

ʾ�� 1��

����: s1 = "abc", s2 = "bca"
���: true 
ʾ�� 2��

����: s1 = "abc", s2 = "bad"
���: false
˵����

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
