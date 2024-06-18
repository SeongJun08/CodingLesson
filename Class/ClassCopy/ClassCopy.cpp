#include <iostream>
/*
class MyClass
{
public:
    int *p;
    
    MyClass()
    {
        p = new int[10];
    }
    ~MyClass()
    {
        delete[] p;
    }
};
*/


/*
class MyClass
{
public:
    int mValue;

public:
    MyClass() : mValue(0)
    {
        std::cout << "[기본생성자]" << mValue << std::endl;
    }
    MyClass(int value) : mValue(value)
    {
        std::cout << "[일반생성자]" << mValue << std::endl;
    }

    MyClass(const MyClass &from)
    {
        mValue = from.mValue;
        std::cout << "[복사생성자]" << mValue << std::endl;
    }
};
*/

class MyClass
{
public:
    int *p;
    int mValue;

public:
    MyClass() : mValue(0)
    {
        p = new int[10];
        std::cout << "[기본생성자]" << p << std::endl;
    }
    MyClass(const MyClass& from)
    {
        p = new int[10];
        for (int i = 0; i < 10; i++)
        {
            p[i] = from.p[i];
        }
        std::cout << "[복사생성자]" << p << std::endl;
        //p = from.p; 얕은복사
    }

    ~MyClass()
    {
        std::cout << "[소멸자]" << p << std::endl;
        delete[] p;
    }
};

int main()
{
    /*
    MyClass a;
    // 문제 없음

    //MyClass b = a;
    MyClass b(a);
    // 문제 발생
    // 얕은 복사 vs 깊은 복사 선택해야된다
    // 제어해야됨
    MyClass b(MyClass());

    std::cout << a.p << std::endl;
    std::cout << b.p << std::endl;
    */

    /*
    MyClass c1(1);
    //MyClass c2(c1);
    //MyClass c2 = c1;
    // c2를 만들어낼 때 c1의 값을 복사해서 c2에 대입한다

    MyClass c2;
    c2 = c1;
    // 그저 값의 대입. 이미 c2의 인스턴스가 생성되어 있으니 값을 복사하여 대입하기만 하면 된다

    c2 = MyClass(2);
    */

    MyClass c1;
    //MyClass c2(c1);

    MyClass c2;

    c2 = c1;
    // 복사는 생성만 필요한 것이 아니다 복사하는 대입 연산자도 필요하다
}
