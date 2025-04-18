#include<iostream>

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
        if (S.size() > length)
        {
            S = S.substr(0, length);
        }
        int temp = 0;
        auto pos = 0;
        while (((pos = S.find(" ",pos)) != std::string::npos) && (pos < temp + length ) ) {
            S.replace(pos, 1, "%20");
            pos += 3;
            temp += 2;
        }
        return S;
    }
};

/*
* ʾ������
*/
class Solution1 {
public:
    std::string replaceSpaces(std::string S, int length) {
        int fillIdx = S.size() - 1;
        int i = 0;
        for (i = length - 1; i >= 0; i--) {
            if (S[i] == ' ') {
                S[fillIdx] = '0';
                S[fillIdx - 1] = '2';
                S[fillIdx - 2] = '%';
                fillIdx -= 3;
            }
            else {
                S[fillIdx] = S[i];
                fillIdx -= 1;
            }
        }
        S = S.substr(1 + fillIdx);
        return S;
    }
};

//int main() {
//    Solution sol;
//    std::string S = "789456  1 23 4";
//    std::string result = sol.replaceSpaces(S, 5);
//    std::cout << result << std::endl;
//    std::cout << "�ַ�����С��" << result.size();
//}