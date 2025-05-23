#include<iostream>
using namespace std;
/*
面试题 01.04. 回文排列
简单
提示
给定一个字符串，编写一个函数判定其是否为某个回文串的排列之一。
回文串是指正反两个方向都一样的单词或短语。排列是指字母的重新排列。
回文串不一定是字典当中的单词。

示例1：
输入："tactcoa"
输出：true（排列有"tacocat"、"atcocta"，等等）

*/

class Solution {
public:
    bool canPermutePalindrome(string s) {
        int num = s.size();
        int counts[256] = { 0 };
        int temp = 0;
        for (int i = 0; i < num; i++)
        {
            counts[s[i]]++; // 增加对应字符的计数
        }
        for (int i = 0; i < 256; i++)
        {
            if (counts[i] % 2 != 0)
            {
                temp++;
            }
        }
        if (temp == 0 || temp == 1)
        {
            return true;
        }
        return false;
    }
};