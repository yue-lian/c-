#include<iostream>
using namespace std;

/*
面试题 01.05. 一次编辑
中等

提示
字符串有三种编辑操作:插入一个英文字符、删除一个英文字符或者替换一个英文字符。 
给定两个字符串，编写一个函数判定它们是否只需要一次(或者零次)编辑。
示例 1：
	输入：
	first = "pale"
	second = "ple"
	输出：True

示例 2：
	输入：
	first = "pales"
	second = "pal"
	输出：False
*/

class Solution {
public:
	bool oneEditAway(string first, string second) {
		int m = first.size();
		int n = second.size();
		if (m - n == 1)
		{
			return oneInsertAway(first, second);
		}
		if (m - n == -1)
		{
			return oneInsertAway(second, first);
		}
		if (m - n == 0)
		{
			bool findDifference = false;
			for (int i = 0; i < m; i++) {
				if (first[i] != second[i])
				{
					if (!findDifference)
					{
						findDifference = true;
					}
					else
					{
						return false;
					}
				}
			}
			return true;	
		}

		return false;
	}
	
	bool oneInsertAway(string longStr, string shortStr) {
		int m = longStr.size();
		int n = shortStr.size();
		int index1 = 0;
		int index2 = 0;
		while (index1 < m && index2 < n)
		{
			if (longStr[index1] == shortStr[index2])
			{
				index2++;
			}
			index1++;
			if (index1 - index2 > 1)
			{
				return false;
			}
		}
		return true;
	}
};

int main() {
	Solution sol;
	string first  = "teacher";
	string second = "bteacher";
	bool result = sol.oneEditAway(first, second);
	cout << result;
}

