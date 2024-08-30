#include <iostream>

bool IsPalindrome(std::string s)
{
    std::string temp{ "" };

    for (auto c : s)
    {
        if (c <= 'z' && c >= 'a')
        {
            temp += c;
        }
        else if (c <= 'Z' && c >= 'A')
        {
            temp += (char)(c - 32);
        }
    }

    int start = 0;
    int end = temp.size() - 1;

    while (start < end)
    {
        if (temp[start] != temp[end])
        {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

int main()
{
    std::cout << "Hello World!\n";
}
