#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>

class MyClass
{
public:
    int mValue;

public:
    MyClass(int val) : mValue(val) {}

    friend std::ostream &operator << (std::ostream &os, const MyClass &param)
    {
        os << param.mValue;
        return os;
    }

    bool operator < (const MyClass &param)
    {
        return mValue < param.mValue;
    }

    //friend bool MyCompare(const MyClass &a, const MyClass &b);
};

bool MyCompare(const MyClass &a, const MyClass &b)
{
    return a.mValue < b.mValue;
}

//class MyClass
//{
//    operator()
//};
//
//MyClass c1;
//
//c1();


int main()
{
    //int array1[5] = { 1,2,3,4,5 };
    //for (int i = 0; i < 5; i++)
    //{
    //    std::cout << array1[i] << std::endl;
    //}

    //for (int e : array1)
    //{
    //    std::cout << e << std::endl;
    //}

    //std::array<int, 5> array2{ 1,2,3,4,5 };
    //for (int i = 0; i < array2.size(); i++)
    //{
    //    std::cout << array2[i] << std::endl;
    //}

    //std::array<int, 5>::iterator itr = array2.begin();
    //while (itr != array2.end())
    //{
    //    std::cout << *itr << std::endl;
    //    itr++;
    //}

    //for (auto it = array2.begin(); it != array2.end(); it++)
    //{
    //    std::cout << *it << std::endl;
    //}

    ////range based for
    //for (int &value : array2)
    //{
    //    std::cout << value << std::endl;
    //}

    //for (int &value : array2)
    //{
    //    //value = *it;
    //    // 원소를 복사해서 value로 가져간거임
    //    
    //    value = 1;
    //}

    //// 이터레이터를 사용해 출력
    //std::array<int, 5> container{ 5,2,1,3,4 };
    //std::array<int, 5>::iterator itr = container.begin();
    //while (itr != container.end())
    //{
    //    std::cout << *itr << std::endl;
    //    itr++;
    //}

    //// 범위기반 반복문으로 최소값을 구하기
    //int min = container[0];
    //for (auto e : container)
    //{
    //    if (e < min)
    //    {
    //        min = e;
    //    }
    //}
    //std::cout << min << std::endl;

    //auto result = std::min_element(container.begin(), container.end());
    //std::cout << *result << std::endl;

    //int sum = std::accumulate(container.begin(), container.end(), 0);
    //std::cout << sum << std::endl;
    //std::cout << sum / container.size() << std::endl;

    std::array<MyClass, 4> container{ MyClass(4),MyClass(3) ,MyClass(2) ,MyClass(1) };
   /* for (const auto &e : container)
    {
        std::cout << e << std::endl;
    }

    auto itr = std::min_element(container.begin(), container.end(), 
        [] (const MyClass &a, const MyClass &b) -> bool 
        { return a.mValue < b.mValue; });
    std::cout << *itr << std::endl;*/

    std::for_each(container.begin(), container.end(), 
        [](const MyClass &a)
        { std::cout << a.mValue << std::endl; });

}
