#include <iostream>

// 사용자에게 정수를 입력받아서 해당 크기의 배열을 동적으로 생성하고 모든 원소를 1로 초기화한 후 출력하는 프로그램
// 위 배열의 크기를 3개로 줄이거나 늘려보자

int main()
{
    std::cout << "input size : ";
    int arraySize{};
    std::cin >> arraySize;

    int *pArray = new int[arraySize];

    if (pArray)
    {

        for (int i = 0; i < arraySize; i++)
        {
            pArray[i] = 1;
        }

        std::cout << " - array - " << std::endl;
        for (int i = 0; i < arraySize; i++)
        {
            std::cout << pArray[i] << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "out of memory" << std::endl;
        return 0;
    }

    int newSize;
    std::cout << "input new size : ";
    std::cin >> newSize;

    int *pTemp = new int[newSize] {};

    // 기존 데이터를 복사
    int maxSize = (newSize > arraySize) ? arraySize : newSize;
    for(int i =0; i < maxSize; i++)
    if (newSize > arraySize)
    {
        //arraySize
        pTemp[i] = pArray[i];
    }

    delete[] pArray;
    pArray = pTemp;
    arraySize = newSize;

    std::cout << " - array - " << std::endl;
    for (int i = 0; i < arraySize; i++)
    {
        std::cout << pArray[i] << " ";
    }
    std::cout << std::endl;
    
    delete[] pArray;
}
