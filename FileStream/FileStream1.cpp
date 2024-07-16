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
    if (ifs.eof())
    {
        return ifs;
    }
    m.mName = buffer;
    std::getline(ifs, buffer, ',');
    m.mLevel = std::stoi(buffer);
    std::getline(ifs, buffer, ',');
    m.mHP = std::stoi(buffer);
    std::getline(ifs, buffer);
    m.mMP = std::stoi(buffer);
    
    return ifs;
}

std::ofstream &operator << (std::ofstream &ofs, Monster &m)
{
    ofs << m.mName << "," << m.mLevel << "," << m.mHP << "," << m.mMP << std::endl;
    

    return ofs;
}

void LoadFile(const char *filepath, std::vector<Monster> &monsters)
{
    try
    {
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
        while (ifs && !ifs.eof())
        {
            Monster m;
            ifs >> m;
            monsters.push_back(m);
        }

        ifs.close();
    }
    catch (...)
    {

    }
}

void SaveFile(const char *filepath, const std::vector<Monster> &monsters)
{
    std::ofstream ofs(filepath);

    ofs << "Name,Level,HP,MP" << std::endl;
    for (auto e : monsters)
    {
        ofs << e;
    }

    ofs.close();
}

void SaveFileBinary(const char *filepath, const std::vector<Monster> &monsters)
{
    std::ofstream ofs(filepath, std::ofstream::binary);

    for (auto e : monsters)
    {
        size_t strLen{ e.mName.length() };
        ofs.write((char *)&strLen, sizeof(size_t));
        ofs.write(e.mName.c_str(), strLen);

        ofs.write((char *)&e.mLevel, sizeof(int));
        ofs.write((char *)&e.mHP, sizeof(int));
        ofs.write((char *)&e.mMP, sizeof(int));
    }
    ofs.close();
}

void LoadFileBinary(const char *filepath, std::vector<Monster> &monsters)
{
    std::ifstream ifs(filepath, std::istream::binary);

    while(ifs)
    {
        
        Monster m;
        size_t strLen{};
        ifs.read((char*) & strLen, sizeof(size_t));

        if (ifs.eof())
        {
            break;
        }

        m.mName.resize(strLen);
        ifs.read(&m.mName[0], strLen);
        ifs.read((char *)&m.mLevel, sizeof(int));
        ifs.read((char *)&m.mHP, sizeof(int));
        ifs.read((char *)&m.mMP, sizeof(int));

        monsters.push_back(m);
    }

    ifs.close();
}

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
    
    /*std::vector<Monster> monsters;

    LoadFile("Data/SimpleData.txt", monsters);
    monsters.push_back({ "Dragon", 20,20,20 });
    SaveFile("Data/SimpleData.txt", monsters);*/

    //// 바이너리 모드
    //std::ofstream ofs("Data/binaryData.bin", std::ofstream::binary);
    //int value{ 1 };
    //ofs.write((char*)&value,sizeof(int));
    //float value2{ 3.14f };
    //ofs.write((char *)&value2, sizeof(float));
    ////POD
    //struct MyData
    //{
    //    int x;
    //    float y;
    //    bool z;
    //};
    //MyData d1{ 1,1.1f,true };
    //ofs.write((char *)&d1,sizeof(MyData));
    //ofs.close();

    std::vector<Monster> monsters
    {
        {"Jelly",1,1,1},
        {"Wolf",5,5,5},
        {"Demon",10,10,10},
    };

    SaveFileBinary("Data/BinaryData.bin", monsters);

    monsters.clear();
    LoadFileBinary("Data/BinaryData.bin", monsters);
}
