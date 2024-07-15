#include <iostream>
#include <fstream>      // file stream object
#include <string>
#include <vector>

struct Monster
{
    std::string mName;
    int mLevel;
    int mHP;
    int mMP;
};

std::ifstream &operator >> (std::ifstream& ifs, Monster& m)
{
    std::string buffer;

    std::getline(ifs, buffer, ',');
    m.mName = buffer;
    std::getline(ifs, buffer, ',');
    m.mLevel = std::stoi(buffer);
    std::getline(ifs, buffer, ',');
    m.mHP = std::stoi(buffer);
    std::getline(ifs, buffer);
    m.mMP = std::stoi(buffer);

    return ifs;
}

// {SLIME, 1, 1, 1}
// {WOLF, 5, 5, 5}
// {DEMON, 10, 10, 10}

int main()
{
    // C++ File Management
    // 1. File Stream Object
    // 2. 파일을 열기
    // 3. 쓰거나 읽기
    // 4. 파일을 닫기


    // \ : escape sequence
    // input file stream
    // 절대경로
    //std::ifstream ifs("D:/Class/Coding/CodingClass/FileStream1/Data/SimpleData.txt");
    //"D:\\Class\\Coding\\CodingClass\\FileStream1\\Data\\SimpleData.txt"
    // 상대경로 - 실행파일에 상대적인 위치
    //std::ifstream ifs("Data/SimpleData.txt");
    std::ifstream ifs("./Data/SimpleData.txt");
    if (ifs)
    {
        std::cout << "File Open" << std::endl;
    }
    else
    {
        std::cout << "File Not Found" << std::endl;
    }

    // 제목 건너뛰기
    std::string buffer;
    std::getline(ifs, buffer);

    // 데이터
    std::vector<Monster> monsters;
    while (ifs && !ifs.eof())
    {
        Monster m;
        ifs >> m;
        monsters.push_back(m);
    }

    ifs.close();

}
