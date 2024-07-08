#include <iostream>
#include <queue>
#include <vector>

int main()
{
    /*
    * 주로 쓴다 
    std::priority_queue<int> pq;

    pq.push(1);
    pq.push(2);
    pq.push(3);
    pq.push(4);
    pq.push(5);

    std::cout << pq.top() << std::endl;
    pq.pop();
    std::cout << pq.top() << std::endl;
    pq.pop();
    std::cout << pq.top() << std::endl;
    pq.pop();
    std::cout << pq.top() << std::endl;
    pq.pop();
    std::cout << pq.top() << std::endl;
    pq.pop();
    */

    // 쓰기 귀찮은 방법
    std::vector<int> v{ 1,2,3,4,5 };

    // heapify 힙 화
    std::make_heap(v.begin(), v.end());

    for (const auto &e : v)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    std::cout << v.front() << std::endl;
    std::pop_heap(v.begin(), v.end());
    v.pop_back();

    std::cout << v.front() << std::endl;
    std::pop_heap(v.begin(), v.end());
    v.pop_back();

    std::cout << v.front() << std::endl;
    std::pop_heap(v.begin(), v.end());
    v.pop_back();
    
}
