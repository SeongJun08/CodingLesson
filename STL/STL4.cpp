#include <iostream>

#include <array>    // std::array
#include <algorithm>    // std::sort
#include <vector> // std::vector
#include <string> // std::string
#include <forward_list> // std::forward_list
#include <list> //std::list
#include <deque> // std::deque
 
void ArrayEx()
{
    // std::array
    // 일반 정적 배열 - 컴파일타임에 크기가 고정
    // 연속된 메모리 공간
    // Sequence
    // Random Acces

    // 선언
    std::array<int, 5> arr{ 5,2,4,1,3 };

    // 순회(Traverse)
    for (const auto &e : arr)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    // 크기
    std::cout << arr.size() << std::endl;

    // 정렬
    std::sort(arr.begin(), arr.end());

    // 인덱스
    std::cout << arr[0] << " : " << (*arr.begin()) << " : " << arr.front() << std::endl;
    std::cout << arr[4] << " : " << *(arr.end()-1) << " : " << arr.back() << std::endl;
}

void VectorEx()
{
    // std::vector
    // 동적 배열
    // 연속된 메모리 공간
    // Sequence
    // Random Access

    // 선언
    std::vector<int> vec{ 5,2,1,3,4 };

    // 크기
    std::cout << vec.size() << std::endl;

    // 정렬
    std::sort(vec.begin(), vec.end());

    // 순회
    for (const auto &e : vec)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    // 인덱스
    std::cout << vec[0] << " : " << *vec.begin() << " : " << vec.front() << std::endl;
    std::cout << vec[4] << " : " << *(vec.end() - 1) << " : " << vec.back() << std::endl;

    // 동적 배열이므로 사이즈 변경이 가능
    vec.resize(10, -1);

    for (const auto &e : vec)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    // 뒤에서 추가/삭제가 빠름
    vec.push_back(6);
    vec.push_back(10);

    vec.pop_back();

    for (const auto &e : vec)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    std::cout << vec.size() << " vs" << vec.capacity() << std::endl;
}

void StringEx()
{
    // std::string
    // 내부적으로 std::vector<char> 유사
    // 문자열에 특화된 기능 추가
    
    // 선언
    std::string str = "hello";
    std::string str2 = { 'h', 'e','l','l','o', '\0'};

    // 크기
    std::cout << str.size() << std::endl;

    // 정렬
    std::sort(str.begin(), str.end());

    std::cout << str << std::endl;
    // 순회
    for (const auto &e : str)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    str.push_back('!');
    str.push_back('?');
    str.pop_back();
    std::cout << str << std::endl;

    // 인덱스
    std::cout << str[0] << " : " << *str.begin() << " : " << str.front() << std::endl;
    std::cout << str[5] << " : " << *(str.end() - 1) << " : " << str.back() << std::endl;

    std::cout << str.substr(0, 3) << std::endl;
    //std::cout << str.starts_with("eh") << std::endl;
}

void ForwardListEx()
{
    // std::forward_list
    // Single Linked list
    // Sequential
    // Random Access 불가능

    // 선언
    std::forward_list<int> list{ 5,3,1,2,4 };

    // 크기
    // size()가 없음
    int count{};
    auto itr = list.begin();
    while (itr != list.end()) { count++; itr++; }
    std::cout << count << std::endl;

    //std::array<int, 5> c1; // c1.size() O(1)
    //std::vector<int> c2;   // c2.size() O(1)
    //std::list<int> c3;     // c3.size() O(n)

    // 정렬
    // Random Access Iterator 없으므로
    //std::sort(list.begin(), list.end());
    list.sort();

    // 순회
    for (auto e : list)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    // 인덱스 불가능
    std::cout << *list.begin() << " : " << list.front() << std::endl;
    // 단방향이라서 이터레이터 - 연산이 불가능 & back 불가능
    // std::cout << *(list.end() - 1) << " : " << list.back();

    // 링크드 리스트의 장점 - 중간에 추가
    //std::forward_list<int>::iterator
    auto result = std::find(list.begin(), list.end(), 4);
    list.insert_after(result, 0);

    for (auto e : list)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

void ListEx()
{
    // std::list
    // double linked list
    // Sequential
    // Random Access X
    
    // 선언
    std::list<int> list{ 5,4,1,3,2 };

    // 크기
    std::cout << list.size() << std::endl;

    // 정렬
    // Random Access X
    // std::sort(list.begin(), list.end());
    list.sort();

    // 순회
    for (const auto &e : list)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    // 인덱스 X
    std::cout << *list.begin() << " : " << list.front() << std::endl;
    std::cout << list.back() << std::endl;

    // list 특징
    list.push_back(10);
    list.push_front(0);

    list.insert(std::find(list.begin(), list.end(), 4), 0);
    for (const auto &e : list)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    list.pop_back();
    list.pop_front();
}

void DequeEx()
{
    // Double Ended Queue
    // std::vector와 유사 - 작은 배열들의 블록

    // 선언
    std::deque<int> c = { 5,4,1,3,2 };

    // 크기
    std::cout << c.size() << std::endl;

    // 정렬
    std::sort(c.begin(), c.end());

    // 순회
    for (const auto& e : c)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    // 인덱스
    std::cout << c[0] << " : " << *c.begin() << " : " << c.front() << std::endl;
    std::cout << c[4] << " : " << *(c.end() - 1) << " : " << c.back() << std::endl;

    // 특징
    c.push_back(10);
    c.push_front(0);

    for (const auto &e : c)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

int main()
{
    // Sequence Container
    ArrayEx();
    std::cout << "----------------------" << std::endl;
    VectorEx();
    std::cout << "----------------------" << std::endl;
    StringEx();
    std::cout << "----------------------" << std::endl;
    ForwardListEx();
    std::cout << "----------------------" << std::endl;
    ListEx();
    std::cout << "----------------------" << std::endl;
    DequeEx();
}
