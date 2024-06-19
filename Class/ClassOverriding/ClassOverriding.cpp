#include <iostream>

// OOP
// 클래스
// 객체
// 캡슐화
// 상속
// 다형성 (Polymorphism)
// PoliceCar is-a Car
// Cat is-a Animal

// Member Function Overriding(재정의)
/*
class Parent
{
public:
    void Function()
    {
        std::cout << "Hello Parent" << std::endl;
    }
};

class Child : public Parent
{
public:
    int mValue;

public:
    void Funciton()
    {
        std::cout << "Hello Child" << std::endl;
    }
};
*/

class Character
{
public:
    // 가상함수 : 자식 클래스에서 재정의(오버라이드)할 것으로 기대하는 멤버함수
    virtual void Attack()
    {
        std::cout << "Character::Attack" << std::endl;
    }
};

class Warrior : public Character
{
public:
    void Attack() override       // 재정의 - 오버라이드, 실수를 막기위해, 편의성을 위해 자식에 override라고 표시를 해둔다   
    {
        std::cout << "전사는 칼을 휘둘렀다" << std::endl;
    }
    // 칼을 휘둘러 공격
    
};

class Thief : public Character
{
public:
    void Attack()
    {
        std::cout << "도적은 그림자에 숨었다" << std::endl;
    }
    // 은신으로 배후 공격
};

class Wizard : public Character
{
public:
    void Attack()
    {
        std::cout << "마법사는 파이어볼을 외웠다" << std::endl;
    }
    // 파이어볼을 발사
};

int main()
{
    //// 생성 : Parent -> Child
    //Child c1;
    //Parent *p = &c1;
    //p->Function();

    Character *party[3]
    {
        new Warrior(),
        new Thief(),
        new Wizard()
    };

    for (int i = 0; i < 3; i++)
    {
        party[i]->Attack();
    }

    for (int i = 0; i < 3; i++)
    {
        delete party[i];
    }
}
