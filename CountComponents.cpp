#include <vector>
#include <iostream>

using namespace std;

int CountComonents(int n, vector< vector<int> > &edges)
{
    auto temp{ edges };

    for (int p1{}; p1 < temp.size(); ++p1)
    {
        for (int p2{ p1 + 1 }; p2 < temp.size(); ++p2)
        {
            for (auto e : temp[p1])
            {
                for (auto f : temp[p2])
                {
                    if (e == f)
                    {
                        temp[p1].insert(temp[p1].end(), temp[p2].begin(), temp[p2].end());
                        temp[p2].clear();
                    }
                }
            }
        }
    }

    int answer{};
    for (auto e : temp)
    {
        if (!e.empty()) answer++;
    }
    return answer;
}


int main()
{
    vector<vector<int>> edges{ {0,1}, {1,2}, {2,3} ,{3,4} };

    cout << CountComonents(5, edges) << std::endl;

    vector<vector<int>> edges2{ {0,1}, {1,2}, {3,4} };
    cout << CountComonents(5, edges2) << std::endl;

}

