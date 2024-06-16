#include <iostream>

// POD : Plain Old Data 구조가 간단하고 옛날부터 써온 데이터
// C언어 타입 int, float

/*
struct MyData
{
    int age;
    int height;
    int weight;

};
*/
/*
class MyClass
{
    //public:
    // MyClass() = default;     기본생성
    // ~MyClass() = default;    기본소멸
    // 생성자 : 반환값이 없음
    // 소멸자 : 반환값이 없고 매개변수 없음

private:
    int age;
public:
    int height;
protected:
    int weight;
};
*/

/*
class Mouse
{
private:
    int mPrice;
    int mDpi;

public:
    Mouse()
    {
        mPrice = 0;
        mDpi = 0;
    }

    Mouse(int price, int dpi = 100)
    {
        mPrice = price;
        mDpi = dpi;
    }
};
*/

/*
class MyClass
{
public:
    int x;
    int y;

    MyClass(int x, int y)
    {
        this->x = x;
        this->y = y;
        std::cout << "HERE" << std::endl;
    }
};
*/

/*
class int
{
    int mValue;

public:
    int(int x)
    {
        mValue = x;
    }
}
*/

/*
class MyClass
{
public:
    int value;

public:
    MyClass(int x)
    {
        value = x;
        std::cout << "HERE" << std::endl;
    }
};
*/

/*
class ClassA
{
public:
    ClassA(int x)
    {
        ClassA(1);    // 생성자는 함수 호출과 헷갈리면 안된다
        //int(1);     //리터럴 1
        //1;
    }
};
*/

// 멤버 초기화 리스트 (member initialize list)
class Keyboard
{
private:
    int mPrice;
    int mKeys;
    const int mType;

public:
    Keyboard() : Keyboard(0,0,0)        //mPrice(0), mKeys(0), mType(0)
    {
        // 중복 코드 발생 우려
        std::cout << "여기에서 ->" << std::endl;
        mPrice = 100;

        //Keyboard(0,0,0);        // 멤버는 안바뀐다
        //1;                    // 생성자는 함수의 형태를 가지고 있으나 함수가 아니다

        std::cout << mPrice << std::endl;
    }

    Keyboard(int price,int keys, int type) : mPrice(price), mKeys(keys), mType(type)
    {
        // 변수의 정의
        //mPrice = price;
        //mKeys = keys;
        //mType = type;

        // 블루투스 버튼 켜기()
        // 페어링()
        std::cout << "여기" << std::endl;
    }
};

/*
class ClassA
{
public:
    ClassA()
    {
        std::cout << "A" << std::endl;
    }
};

class ClassB
{
public:
    ClassB()
    {
        std::cout << "B" << std::endl;
    }
};

class ClassC
{
    ClassA a;
    ClassB b;

public:
    ClassC() : a(), b()             //멤버초기화는 순서대로 하는것이 헷갈리지 않는다
    {
        std::cout << "C" << std::endl;
    }
};
*/

int main()
{
    /*
    std::cout <<"int : " << std::is_pod<int>::value << std::endl;
    std::cout << "struct : " << std::is_pod<MyData>::value << std::endl;
    std::cout << "class : " << std::is_pod<MyClass>::value << std::endl;
    */
    
    /*
    // Mouse를 반환하는 m1이라는 함수를 선언한다
    //Mouse m1();
    // 함수와 헷갈려서 매개변수 없을 시 () 빼야됨
    // 유니폼 초기화를 사용
    Mouse m1{};               // 매개변수없음     Mouse()
    Mouse m2{ 100, 300 };     // 매개변수 두개    Mouse(int, int)
    Mouse m3{ 100 };          // 하나 기본값      Mouse(int, int=100)

    //MyClass c1{1,1};      // 클래스 유니폼 초기화는 생성자 우선, 생성자 없으면 멤버
    */

    /*
    int a1 = int(1);        //copy initialize       int a1 = 1
    int a2(2);              // direct initialize
    int a3{ 3 };            // uniform intialize
    int a4 = int{ 4 };      // uniform copy initialize   int a4 = {4};

    MyClass c1 = MyClass(1);        //copy initialize
    MyClass c2(2);                  //copy initialize
    MyClass C3{ 3 };                // uniform intialize
    MyClass c4 = MyClass{ 4 };      // uniform copy initialize
    */

    //Keyboard k1(1000, 103, 1);

    //ClassC c;
    /*
    ClassB instance;
    // 메모리 공간(객체)은 B가 먼저 만들어지고 A가 만들어짐
    // 생성자는 A가 만들어지고 나서 B가 만들어짐
    */

    Keyboard k1;
    //ClassA a1(1);
}

