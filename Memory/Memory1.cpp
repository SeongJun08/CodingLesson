#include <iostream>

// C++ Momory Management - 변수의 삶과 죽음 lifecycle
// 1. 자동 - 지역변수, 매개변수 
// 2. 정적(static) - static 변수, global 변수
// 3. 동적(dynamic)

int global = 2;

void Function(int x)
{
    static int y = 1;
}

int main()
{
    int x; // 여기서 생성

    for(int i = 0; i < 10; i++)
    {
        int x;
    }

}// x 자동으로 사라짐
