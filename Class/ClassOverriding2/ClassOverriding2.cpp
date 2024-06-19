#include <iostream>


class Parent
{
public:
    void F1()
    {
        std::cout << "1.Parent::F1()" << std::endl;
    }
    virtual void F2()
    {
        std::cout << "2.Parent::F2()" << std::endl;
    }
};

class Child : public Parent
{
public:
    void F1() { std::cout << "3.Child::F1()" << std::endl; }
    void F2() override { std::cout << "4.Child::F2()" << std::endl; }
};

// f라는 객체와 f(){} 내용을 바인딩 - 컴파일
// 선언
void f();

// 정의
void f()
{

}

int main()
{
   /* Parent *pP = new Parent;
    Child *pC = new Child;

    pP->F1();
    pP->F2();
    pC->F1();
    pC->F2();

    Parent *p = pC;
    p->F1();
    p->F2();
    

    delete pC;
    delete pP;*/

    // x라는 객체와 10이라는 값이 바인딩
    // 컴파일 타임 바인딩, 이른 바인딩, 정적 바인딩
    int x = 10;
    const int y = 10;

    Character *party[5];
    A마을();
    B마을();
    C마을();

    // 런타임 바인딩, 늦은 바인딩, 동적 바인딩
    party[0]->Attack();
    int *p1 = new int;
    const int *p2 = new int;
}
