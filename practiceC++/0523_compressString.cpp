/*
������ 01.06. �ַ���ѹ��
��

��ʾ
�ַ���ѹ���������ַ��ظ����ֵĴ�������дһ�ַ�����ʵ�ֻ������ַ���ѹ�����ܡ�
���磬�ַ���aabcccccaaa���Ϊa2b1c5a3������ѹ��������ַ���û�б�̣��򷵻�ԭ�ȵ��ַ�����
����Լ����ַ�����ֻ������СдӢ����ĸ��a��z����

ʾ�� 1��

���룺"aabcccccaaa"
�����"a2b1c5a3"
ʾ�� 2��

���룺"abbccd"
�����"abbccd"
���ͣ�"abbccd"ѹ����Ϊ"a1b2c2d1"����ԭ�ַ������ȸ�����
��ʾ��

�ַ��������� [0, 50000] ��Χ�ڡ�
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