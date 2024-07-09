#include <iostream>
#include <map>
#include <string>
#include <vector>

// Time Complexity : O(2^n)
// Space Complexity : O(n)
long long Fibonacci(int n)
{
    // base case
    if (n <= 2)
    {
        return 1;
    }

    // recursive case
    return Fibonacci(n - 1) + Fibonacci(n - 2);
} 

// Time Complexity : O(n)
// Space Complexity : O(n + n) = O(2n) = O(n)
int64_t Fibonacci_Memo(int n, std::map<int, int64_t>& memo)
{
    // memo
    if (memo.count(n) == 1)
    {
        return memo[n];
    }

    // base case
    if (n <= 2)
    {
        return 1;
    }

    // recursive case
    memo[n] = Fibonacci_Memo(n - 1, memo) + Fibonacci_Memo(n - 1, memo);
    return memo[n];
    
}

// m x n 크기의 사각형이 주어졌을 때, 좌상단에서 출발하여 우하단으로 이동하는 모든 경우의 수를 구하시오 (재귀)
// 단, 오른쪽이나 아래쪽으로만 이동 가능
// Time Complexity : O( 2 ^ (m + n))
// Space Complexity : O(m + n)
int64_t FindWays(int m, int n)
{
    // base case
    if (m == 0 || n == 0)
    {
        return 0;
    }

    if (m == 1 || n == 1)
    {
        return 1;
    }

    // recursive case
    return FindWays(m - 1, n) + FindWays(m, n - 1);
}

// Time Complexity : O( 2 * (m + n)) = O(m + n)
// Space Complexity : O(m + n)
int64_t FindWays_Memo(int m, int n, std::map<std::string, int64_t>& memo)
{
    const std::string key = std::to_string(m) + "," + std::to_string(n);

    if (memo.count(key) == 1)
    {
        return memo[key];
    }

    const std::string rkey = std::to_string(n) + "," + std::to_string(m);
    if (memo.count(rkey) == 1)
    {
        return memo[rkey];
    }

    // base case
    if (m == 0 || n == 0)
    {
        return 0;
    }

    if (m == 1 || n == 1)
    {
        return 1;
    }

    // recursive case
    memo[key] = FindWays_Memo(m - 1, n, memo) + FindWays_Memo(m, n - 1, memo);
    return memo[key];
}

// 정수의 배열 numbers에서 숫자들을 조합하여 sum을 만들어 낼 수 있는지 확인하는
// bool CanAccumlation(sum, numbers)를 만들어 보세요.
// 단, 동일한 원소를 여러번 사용해도 된다
// 원소는 0이 아닙니다 sum은 양수입니다
// ex) 8 {2, 3, 5}
// True 
// ex) 8 {5,6}
// false
// Time Complexity : O( 너비 x 높이) = O (m x n)
// Space Complexity : O(m)
bool CanAccumlation(int sum, const std::vector<int>& numbers)
{
    //base case
    if (sum == 0)
    {
        return true;
    }
    if (sum < 0)
    {
        return false;
    }

    // recursive case
    for (const auto &e : numbers)
    {
        if (CanAccumlation(sum - e, numbers))
        {
            return true;
        }
    }

    return false;
}

// Time Complexity : O( m x n)
// Space Complexity : O(2m) = O(m)
bool CanAccumlation_Memo(int sum, const std::vector<int> &numbers, std::map<int, bool> &memo)
{
    if (memo.count(sum) == 1)
    {
        return memo[sum];
    }

    //base case
    if (sum == 0)
    {
        return true;
    }
    if (sum < 0)
    {
        return false;
    }

    // recursive case
    for (const auto &e : numbers)
    {
        if (CanAccumlation_Memo(sum - e, numbers, memo))
        {
            memo[sum] = true;
            return memo[sum];
        }
    }

    memo[sum] = false;
    return memo[sum];
}

// 정수의 배열 numbers에서 숫자들을 조합하여 sum을 만들어 낼 수 있는지 확인하는
// bool CanAccumlation(sum, numbers)를 만들어 보세요.
// 단, 동일한 원소를 여러번 사용해도 된다
// 원소는 0이 아닙니다 sum은 양수입니다
// ex) 8 {2,3,5}
//      {{2,3,3} or {2,2,2,2}}
// ex) 8 {5,6}
//      nullptr
// ex) 0 {5,6}
//      {}

// Time Complexity : O( n^m ) -> O(m * n)
// Space Complexity : O(m^2) -> O( m^2 ) 입출력을 무시한다면 O(m)
using accum_memo = std::map<int, std::shared_ptr<std::vector<int>>>;
std::shared_ptr<std::vector<int>> HowAccumulate(int sum, const std::vector<int>& numbers, accum_memo memo)
{
    if (memo.count(sum) == 1)
    {
        return memo[sum];
    }

    // base case
    if (sum == 0)
    {
        return std::make_shared<std::vector<int>>(); // {}
    }
    if (sum < 0)
    {
        return nullptr;
    }

    // recursive case
    for (auto e : numbers)
    {
        auto ret = HowAccumulate(sum - e, numbers, memo);
        if (ret) //ret != nullptr
        {
            ret->push_back(e);
            memo[sum] = ret;
            return memo[sum];
        }
    }

    memo[sum] = nullptr;
    return memo[sum];
}


// 정수의 배열 numbers에서 숫자들을 조합하여 sum을 만들어 낼 수 있는 집합 중 최소 크기의 집합은
// OptimzeAccumulation(sum, numbers)를 만들어 보세요.
// 단, 동일한 원소를 여러번 사용해도 된다
// 원소는 0이 아닙니다 sum은 양수입니다
// ex) 8 {2,3,5}
//      {3,5}
// ex) 8 {5,6}
//      nullptr
// ex) 0 {5,6}
//      {}
std::shared_ptr<std::vector<int>> OptimizeAccumulation(int sum, const std::vector<int> &numbers, accum_memo &memo)
{
    if (memo.count(sum) == 1)
    {
        return memo[sum];
    }

    // base case
    if (sum == 0)
    {
        return std::make_shared<std::vector<int>>();
    }
    if (sum < 0)
    {
        return nullptr;
    }

    // recursive case
    std::shared_ptr<std::vector<int>> best = nullptr;
    for (auto e : numbers)
    {
        auto ret = OptimizeAccumulation(sum - e, numbers, memo);

        if (ret != nullptr)
        {
            std::shared_ptr<std::vector<int>> temp = std::make_shared<std::vector<int>>();
            temp->resize(ret->size());
            std::copy(ret->begin(), ret->end(), temp->begin());
            temp->push_back(e);
            //ret->push_back(e);
            if (best == nullptr || temp->size() < best->size())
            {
                best = temp;
            }
        }
        
    }

    memo[sum] = best;
    return memo[sum];
}

void Print(std::shared_ptr<std::vector<int>> result)
{
    
    if (result)
    {
        std::cout << "{";
        for (auto e : *result)
        {
            std::cout << e << " ";
        }
        std::cout << "}" << std::endl;
    }
    else
    {
        std::cout << "nullptr" << std::endl;
    }
}


int main()
{
    /*for (int i = 1; i < 50; i++)
    {
        std::map<int, int64_t> m;
        std::cout << Fibonacci_Memo(i, m) << " ";
    }
    std::cout << std::endl;*/

    //std::cout << FindWays(30, 30) << std::endl;
    //std::map<std::string, int64_t> memo;
    //std::cout << FindWays_Memo(30, 30 ,memo) << std::endl;

    /*std::cout << CanAccumlation(8, { 2,3,5 }) << std::endl;
    std::cout << CanAccumlation(8, { 5,6 }) << std::endl;
    std::cout << CanAccumlation(999, { 1,2,3,4,5,6,7,8,9 }) << std::endl;*/

    /*std::map<int, bool> memo;
    std::cout << CanAccumlation_Memo(8, { 2,3,5 },memo) << std::endl;
    memo.clear();
    std::cout << CanAccumlation_Memo(8, { 5,6 }, memo) << std::endl;
    memo.clear();
    std::cout << CanAccumlation_Memo(900, { 7, 14 }, memo) << std::endl;*/

    /*accum_memo m;
    Print(HowAccumulate(8, { 2, 3, 5 }, m));
    m.clear();
    Print(HowAccumulate(8, { 5,6 }, m));
    m.clear();
    Print(HowAccumulate(7, { 3,4,5,7 }, m));
    m.clear();
    Print(HowAccumulate(900, { 7,14 }, m));*/

    accum_memo m;
    Print(OptimizeAccumulation(8, { 2, 3, 5 }, m));
    m.clear();
    Print(OptimizeAccumulation(8, { 5,6 }, m));
    m.clear();
    Print(OptimizeAccumulation(7, { 1,3,4,5 }, m));
    m.clear();
    Print(OptimizeAccumulation(900, { 7,14 }, m));
}
