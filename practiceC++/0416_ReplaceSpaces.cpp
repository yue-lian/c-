#include<iostream>
#include <vector>

/*
* ������ 01.03. URL��
��
��ʾ
URL������дһ�ַ��������ַ����еĿո�ȫ���滻Ϊ%20���ٶ����ַ���β�����㹻�Ŀռ��������ַ�������֪���ַ����ġ���ʵ�����ȡ�
��ע����Javaʵ�ֵĻ�����ʹ���ַ�����ʵ�֣��Ա�ֱ���������ϲ�������

ʾ�� 1��

���룺"Mr John Smith    ", 13
�����"Mr%20John%20Smith"
ʾ�� 2��

���룺"               ", 5
�����"%20%20%20%20%20"
 

��ʾ��

�ַ��������� [0, 500000] ��Χ�ڡ�
*/

class Solution {
public:
    std::string replaceSpaces(std::string S, int length) {
        if (length == 0) return "";
        //std::vector<char> table(3*length, 0);
        int temp = 0;
        for (int i = 0; i < length + temp; i++)
        {
            if (1)
            {

            }
        }
    }
};

int main() {
    Solution sol;
    std::cout << sol.replaceSpaces("1 23",4);
}