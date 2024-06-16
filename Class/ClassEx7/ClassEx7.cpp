#include <iostream>

/*
class MyClass
{
public:
    int mValue;

    MyClass(int value) : mValue(value)
    {

    }
    void DoSomething() const
    {

    }
};
*/

/*
void f()
{
    
    static int x = 0;

    x++;
    std::cout << x << std::endl;
}
*/

// static 변수, 한번 만들어지면 다시 초기화 X, 프로그램 끝날때까지 유지
// 멤버 변수 -> 인스턴스
// static 멤버 변수 -> class
// 클래스 변수

/*
class MyClass
{
public:
    static int value;

    MyClass()
    {
        value++;
    }
    ~MyClass()
    {
        value--;
    }
};*/

/*
class MyClass
{
public:
    static void DoSomething();
};

void MyClass::DoSomething()
{
    std::cout << "Me" << std::endl;
} */

/*
class Math
{
public:
    static void Add();
    static void Minues();
    static void Multiply();
};
*/

// 인스턴스에서 만들어지지 않기 때문에 클래스변수를 따로 정의해주어야한다
//int MyClass::value{0};

class MyClass
{
private:
    int value;

public:
    static void DoSomethig(MyClass* p)
    {
        p->value = 0;
    }
};
/*
void MyClass::DoSomethig(MyClss *p)
{
    p.value = 0;
}
*/

int MyClass::value = 0;

int main()
{
    //const MyClass c1(10);

    //c1.mValue = 10;
    //c1.DoSomething();
    //f(); // 1
    //f(); // 2

    //MyClass c1;
    //std::cout << c1.value << std::endl;
    //std::cout << MyClass::value << std::endl;
    /*
    MyClass c1;
    for (int i = 0; i < 4; i++)
    {
        MyClass c2;
    }

    std::cout << MyClass::value << std::endl;
    */

    //MyClass::DoSomething();

    //Math::Add();

    
}
