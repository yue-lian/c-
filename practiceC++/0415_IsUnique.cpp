#include<iostream>
#include<string>
/*
* 250415
面试题 01.01. 判定字符是否唯一
简单
提示
实现一个算法，确定一个字符串 s 的所有字符是否全都不同。

示例 1：

输入: s = "leetcode"
输出: false
示例 2：

输入: s = "abc"
输出: true
限制：

0 <= len(s) <= 100
s[i]仅包含小写字母
如果你不使用额外的数据结构，会很加分。
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
