/*
面试题 01.06. 字符串压缩
简单

提示
字符串压缩。利用字符重复出现的次数，编写一种方法，实现基本的字符串压缩功能。
比如，字符串aabcccccaaa会变为a2b1c5a3。若“压缩”后的字符串没有变短，则返回原先的字符串。
你可以假设字符串中只包含大小写英文字母（a至z）。

示例 1：

输入："aabcccccaaa"
输出："a2b1c5a3"
示例 2：

输入："abbccd"
输出："abbccd"
解释："abbccd"压缩后为"a1b2c2d1"，比原字符串长度更长。
提示：

字符串长度在 [0, 50000] 范围内。
*/
#include<iostream>
#include <sstream>

using namespace std;

class Solution {
public:
    string compressString(string S) {
        int num = S.size();
        string newS = "";
        string temp;
        int count = 1;

        std::ostringstream numStream;

        for (int i = 1; i < num; i++)
        {
            if (S[i - 1] == S[i]) {
                count++;
            }
            else
            {
                numStream << count;
                temp = S[i - 1] + numStream.str();
                newS.insert(newS.size() - 1, temp);
            }
        }
        return newS;
    }
};