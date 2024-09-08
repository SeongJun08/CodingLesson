#include <iostream>
#include <vector>
#include <algorithm>

bool CanAttendMeetings(std::vector<std::vector<int>> &intervals)
{
    if (intervals.size() == 1) return true;
    sort(intervals.begin(), intervals.end());
    for (int i{ 1 }; i < intervals.size(); ++i)
    {
        if (intervals[i][0] < intervals[i - 1][1]) return false;
    }
    return true;
}

int main()
{
    std::vector<std::vector<int>> intervals = { {0,30},{5,10},{15,20} };
    std::cout << CanAttendMeetings(intervals);
}
