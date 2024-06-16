#include <iostream>

class MyClass
{
private:
    int *mP;

public:
    MyClass()
    {
        mP = new int;
    }
    /*
    void Release()
    {
        if (mP)
        {
            delete mP;
            mP = nullptr;
        }
    }
    */

    ~MyClass()
    {
        if (mP)
        {
            delete mP;
            mP = nullptr;
        }
       
    }
};

int main()
{
    MyClass c1;

    //c1.Release();
}
