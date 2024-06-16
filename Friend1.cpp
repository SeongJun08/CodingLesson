#include <iostream>

// 전방선언
class Sword;

// 선언과 정의 분리하기
class Jewel
{
public:
    void Socket(Sword &s);

    /*
    * 얘들은 소드 정보가 필요 없음 오직 소드 소켓에만 소드의 정보를 줄꺼임
    void Socket(Helm &h)
    {
    }
    void Socket(Armmer &g)
    {
    }
    */

};

class Sword
{
    friend class Warrior;
    friend void EnhanceSword(Sword &s);
    /*
    {
        s.mAttackDamage += s.mAttackDamage;
    }
    분리하는것이 헷갈리지 않다
    */

    friend void Jewel::Socket(Sword &s);

private:
    int mAttackDamage;

public:
    Sword(int damage) : mAttackDamage(damage) {}
};


void Jewel::Socket(Sword &s)
{
    std::cout << s.mAttackDamage << "인 무기에 홈을 추가했다." << std::endl;
}


class Warrior
{
public:
    void Attack(Sword& weapon)
    {
        std::cout << "전사는 칼을 휘둘러 " << weapon.mAttackDamage 
            << "만큼 피해를 주었다" << std::endl;
    }
};


void EnhanceSword(Sword& s)
{
    s.mAttackDamage += s.mAttackDamage;
}


int main()
{
    Sword shortSword(10);
    Sword longSword(15);
    Warrior player;

    player.Attack(shortSword);
    player.Attack(longSword);

    EnhanceSword(shortSword);

    player.Attack(shortSword);
}