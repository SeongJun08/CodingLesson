#include <iostream>

class DataClass
{
private:
    int mYear;
    int mMonth;
    int mDay;

public:
    DataClass(int year, int month, int day)
    {
        if (year < 1970 || month < 1 || month > 12 || day < 1 || day > 31)
        {
            std::cout << "Error" << std::endl;
        }
        mYear = year;
        mMonth = month;
        mDay = day;

    }

    void Print()
    {
        std::cout << mYear << "-" << mMonth << "-" << mDay << std::endl;
    }

    void IsLeapYear()
    {
        if (mYear % 4 == 0)
        {
            std::cout << "LeapYear" << std::endl;
        }
        else
        {
            std::cout << "Not LeapYear" << std::endl;
        }
    }
};

int main()
{
    DataClass day(2024, 6, 11);
    day.Print();
    day.IsLeapYear();
}
