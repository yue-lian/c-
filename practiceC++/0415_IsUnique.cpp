#include<iostream>
#include<string>
/*
* 250415
������ 01.01. �ж��ַ��Ƿ�Ψһ
��
��ʾ
ʵ��һ���㷨��ȷ��һ���ַ��� s �������ַ��Ƿ�ȫ����ͬ��

ʾ�� 1��

����: s = "leetcode"
���: false
ʾ�� 2��

����: s = "abc"
���: true
���ƣ�

0 <= len(s) <= 100
s[i]������Сд��ĸ
����㲻ʹ�ö�������ݽṹ����ܼӷ֡�
*/
class Solution {
public:
	bool isUnique(std::string astr) {
		for (int i = 0; i < astr.length(); ++i) {
			for (int j = i + 1; j < astr.length(); ++j) {
				if (astr[i] == astr[j]) {
					return false;
				}
			}
		}
		return true;
	}
};

//int main() {
//	Solution sol;
//	std::string astr = "ABCD";
//	std::cout << std::boolalpha << sol.isUnique(astr) << std::endl;
//}
