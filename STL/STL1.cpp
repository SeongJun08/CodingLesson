#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void StringPrinter(const std::string &input)
{
    std::cout <<  input.length() << " : " << input << std::endl;


}
int main()
{
    //std::string str1;
    //StringPrinter(str1);
    //// unsigned int
    //size_t a;

    //std::string str2("Hello");
    //std::string str3(str2, 0, 5);
    // //n_pos == End
    //StringPrinter(str3);

    //std::string str4(10, 'a');
    //StringPrinter(str4);

    //std::string::iterator itr;
    //itr = str2.begin();

    //std::cout << *itr << std::endl;
    //itr++;
    //std::cout << *itr << std::endl;

    /*std::string::iterator itr2 = str2.begin();
    while (itr2 != str2.end())
    {
        std::cout << *itr2 << std::endl;
        itr2++;
    }*/

    std::string str1("hello");
    std::vector<int> container{ 1,2,3,4,5 };
    /*int result = std::count(str1.begin(), str1.end(), 'l');
    std::cout << result << std::endl;*/
    std::sort(container.begin(), container.end());
    std::string::iterator itr = container.begin();

    // 문자열 <-> 숫자
    // "123"      123
    std::string str1;
    int number = 65;

    str1 = std::to_string(number);
    int number = std::stoi(str1);  // int
    std::stof(str1); // float
    std::stod(str1); // double

    std::cout << str1 << std::endl;
    
}
