#include <iostream>
#include <algorithm>

int MyFunction(int x)
{
    return 0;
}

int MyFunction2(int x)
{
    return 1;
}

int Compare(const void *p1, const void *p2)
{
    int x = *static_cast<const int *>(p1);
    int y = *(const int *)(p2);

    return x - y;
}

int main()
{
    //auto
    auto x = 1;
    int (*pf)(int) = MyFunction;
    auto pf2 = pf;

    // range-based loop
    int array[5]{ 5,2,3,1,4 };
    char str[6]{ "hello" };

    for (const auto &e : str)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    // lambda
    pf = [](int x) -> int {return 1; };
    std::qsort(array, 5, sizeof(int), 
        [](const void *p1, const void *p2) -> int 
        {
            int x = *static_cast<const int *>(p1);
            int y = *(const int *)(p2);
            return y - x;
        });

    for (const auto &e : array)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}
