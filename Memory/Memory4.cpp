#include <iostream>

int main()
{
    /*
    int array1D[10];
    int *p = new int[10];

    //2차 배열을 동적으로 할당
    int array2D[2][3];
    int(*p2)[3] = new int[2][3]{ { 1,2,3}, {4,5,6} };

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << p2[i][j] << std::endl;
        }
    }

    delete[] p2;
    */

    int m = 2;
    int n = 3;

    //int ** p3 = new int[m][n];
    int **p3 = new int *[m];
    for (int i = 0; i < m; i++)
    {
        p3[i] = new int[n];
    }

    // 삭제는 생성의 역순
    for (int i = 0; i < m; i++)
    {
        //p3[i] = new int[n];
        delete[] p3[i];
        p3[i] = nullptr;
    }

    //int **p3 = new int *[m];
    delete[] p3;
    p3 = nullptr;
}
