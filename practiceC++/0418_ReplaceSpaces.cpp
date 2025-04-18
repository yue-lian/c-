#include<iostream>

/*
* 面试题 01.03. URL化
简单
提示
URL化。编写一种方法，将字符串中的空格全部替换为%20。假定该字符串尾部有足够的空间存放新增字符，并且知道字符串的“真实”长度。
（注：用Java实现的话，请使用字符数组实现，以便直接在数组上操作。）

示例 1：

输入："Mr John Smith    ", 13
输出："Mr%20John%20Smith"
示例 2：

输入："               ", 5
输出："%20%20%20%20%20"
 

提示：

字符串长度在 [0, 500000] 范围内。
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
* 示例代码
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
//    std::cout << "字符串大小：" << result.size();
//}