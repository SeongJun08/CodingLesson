#include <iostream>

using Comparison = bool (*) (int, int);

// 오름차순
bool Asscending(int x, int y)
{
    return x > y;
}

// 내림
bool Descending(int x, int y)
{
    return x < y;
}

void Sort(int numbers[], int count, Comparison f)
{
    int temp{};

    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (f(numbers[i], numbers[j]))
            {
                temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;
            }
        }
    }
}

int main()
{
    const int NumArray = 10;
    int scores[NumArray]{ 20,10,40,15,30 };

    Sort(scores, NumArray, Asscending);

    for (int i = 0; i < NumArray; i++)
    {
        std::cout << scores[i] << ",";
    }

}
