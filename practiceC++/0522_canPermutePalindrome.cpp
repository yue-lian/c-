#include<iostream>
using namespace std;
/*
������ 01.04. ��������
��
��ʾ
����һ���ַ�������дһ�������ж����Ƿ�Ϊĳ�����Ĵ�������֮һ��
���Ĵ���ָ������������һ���ĵ��ʻ���������ָ��ĸ���������С�
���Ĵ���һ�����ֵ䵱�еĵ��ʡ�

ʾ��1��
���룺"tactcoa"
�����true��������"tacocat"��"atcocta"���ȵȣ�

*/

class Solution {
public:
    bool canPermutePalindrome(string s) {
        int num = s.size();
        int counts[256] = { 0 };
        int temp = 0;
        for (int i = 0; i < num; i++)
        {
            counts[s[i]]++; // ���Ӷ�Ӧ�ַ��ļ���
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