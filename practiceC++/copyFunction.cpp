#include <iostream>
#include <string>
#define COPY_CASE_


#ifdef COPY_CASE_1
int main()
{
    std::string string = "Cherno";
    std::string second = string;
    second[2] = 'a';
    std::cout << string << std::endl;
    std::cout << second << std::endl;
    std::cin.get();
}
#endif // TEST_CASE_1
