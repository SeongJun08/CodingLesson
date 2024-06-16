#include <iostream>

int main()
{
    /* Queue 만들기
    * 1번 입력시 숫자 저장
    * 숫자는 왼쪽에서부터 오른쪽으로 책장에 책을 넣듯이 저장
    * 2번 입력시 숫자 제거
    * 숫자는 왼쪽에서부터 제거
    */

    int queue[10]{};
    const int enqueue = 1;
    const int dequeue = 2;
    const int shutdown = 3;
    int choose{};
    int value{};
    int layer{};

    while(true)
    {
        std::cout << " 1 : enqueue, 2 : dequeue, 3 : shut down   >  " << std::endl;
        std::cin >> choose;

        if (choose == enqueue)
        {
            std::cout << "value ? " << std::endl;
            std::cin >> value;
            queue[layer++] = value;

            std::cout << "----QUEUE----" << std::endl;

            for (int i = 0; i < layer; i++)
            {
                std::cout << queue[i] << "   ";
            }
            std::cout << std::endl;

        }
        else if (choose == dequeue)
        {

        }

    }


}
