#include <iostream>

//dynamic memory allocation

// run-time (프로그램이 실행될때) : dynamic

int main()
{

    // C
    //memory allocation 메모리 할당시 초기화x
    int *p = (int*)malloc(sizeof(int));

    if (p != nullptr)
    {
        std::cout << *p << std::endl;
        free(p);
    }
    
    //contiguous allocation 메모리 할당시 초기화 -> 초기화 하는만큼 속도 저하
    int*p2 = (int*)calloc(1,sizeof(int));
    if (p2 != nullptr)
    {
        std::cout << *p2 << std::endl;
        free(p2);
    }
    
    //c++
    //연산자

    int *p3 = new int{4};
    if (p3)
    {
        std::cout << *p3 << std::endl;
        delete p3;
    }

    int *scores = new int[10] {};
    if (scores)
    {
        std::cout << scores[0] << std::endl;
        delete[] scores;
    }

    //Student Struct
    struct Student
    {
        int number;
        int score;
    };
    
    //동적으로 학생배열(3명)
    //유니폼초기화 식이 아니라 직접 초기화 해보자
    // {1,10}, {2,100},{3,50}

    Student *p4 = new Student[3];
    if (p4)
    {
        p4[0].number = 1;
        p4[0].score = 10;
        delete[] p4;
    }

  //동적 메모리 할당
// 1. 프로그래머가 마음대로 할당하고 싶을 때
// 2. 반드시 동적으로 할당해야만 하는 경우
// 1024 바이트 = 1k 넘으면 동적으로 만드는게 좋다

  int number;
std::cin >> number;


int *p = new int[sizeof(number)];

for (int i = 0; i < number; i++)
{
    p[i] = 1;
    std::cout << *p << std::endl;
}

if (p)
{
    *p = 0;
}

delete p;
p = nullptr;


}
