#include <iostream>

// 멤버 변수의 숨김 현상

class Parent
{
//protected:
public:
    int mValue;

public:
    Parent() { std::cout << "+Parent(1) " << std::endl; }      // 3번순서
    Parent(int value) { std::cout << "+Parent(2) " << std::endl; }   
    ~Parent() { std::cout << "-Parent" << std::endl; }      // 5번순서

    int GetParentValue() { return mValue; }
};

class Child : public Parent
{
//protected:
public:
    int mValue;

public:
    // 대리 생성자
    Child() : Parent(1), mValue(1)      // Parent() 숨어있음, 2번순서 ,   Parent()는 대리생성자처럼 보이지만 부모클래스의 생성자를 부르는거임
    { std::cout << "\t+Child" << std::endl; }
    ~Child() { std::cout << "\t-Child" << std::endl; }      // 4번순서
};

//class MyClass
//{
//    int mValue;
//
//public:
//    MyClass() : MyClass(0)/*, mValue(0)*/ {}     //  대리 생성자 MyClass(0) 와 멤버 초기화식 mValue(0) 은 같이 쓸 수 없다 중복되니까
//    MyClass(int v) : mValue(v) {}
//};

int main()
{
    // 생성 : Parent -> Child
    Child c1;       // 1번순서
    c1.mValue = 100;      // 멤버 변수 숨김
    // 소멸 Child -> Parent

    
    // 멤버 변수의 숨김 현상
    std::cout << c1.mValue << std::endl;
    std::cout << c1.Parent::mValue << std::endl;
    std::cout << c1.Child::mValue << std::endl;
    std::cout << c1.GetParentValue() << std::endl;
}
