#include<iostream>
using namespace std;

/*
������ 01.05. һ�α༭
�е�

��ʾ
�ַ��������ֱ༭����:����һ��Ӣ���ַ���ɾ��һ��Ӣ���ַ������滻һ��Ӣ���ַ��� 
���������ַ�������дһ�������ж������Ƿ�ֻ��Ҫһ��(�������)�༭��
ʾ�� 1��
	���룺
	first = "pale"
	second = "ple"
	�����True

ʾ�� 2��
	���룺
	first = "pales"
	second = "pal"
	�����False
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

