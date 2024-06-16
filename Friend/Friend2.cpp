#include <iostream>

class Point2D
{
private:
    int mX;
    int mY;

public:
    //Point2D() = default;
    
    Point2D() {/*std::cout << "[+] (0,0)" << std::endl; */}
    Point2D(int x, int y) : mX(x), mY(y) {/*std::cout << "[+] "; Print();*/}

    void Print() {std::cout << "(" << mX << "," << mY << ")" << std::endl;}

    //friend Point2D operator +(Point2D lhs, Point2D rhs);
    //friend Point2D operator +(cosnt Point2D& lhs, const Point2D& rhs);
    /*
    Point2D operator + (Point2D rhs)
    {
        Point2D result;
        result.mX = this->mX + rhs.mX;
        result.mY = this->mY + rhs.mY;

        return result;
    }
    */

    Point2D operator +(const Point2D &rhs)
    {
        Point2D result;
        result.mX = this->mX + rhs.mX;
        result.mY = this->mY + rhs.mY;

        return result;
    }

    friend Point2D operator +(const Point2D& lhs, const Point2D& rhs);
    

    Point2D operator -(const Point2D &rhs)
    {
        Point2D result;
        result.mX = this->mX - rhs.mX;
        result.mY = this->mY - rhs.mY;

        return result;
    }

    Point2D operator *(const int rhs)
    {
        Point2D result;
        result.mX = this->mX * rhs;
        result.mY = this->mY * rhs;

        return result;
    }

    Point2D operator / (const int rhs)
    {
        Point2D result;
        result.mX = this->mX / rhs;
        result.mY = this->mY / rhs;

        return result;
    }

    friend std::ostream &operator << (std::ostream &os, Point2D pt);
};

/*
Point2D operator +(Point2D lhs, Point2D rhs)
{
    Point2D result;
    result.mX = lhs.mX + rhs.mX;
    result.mY = lhs.mY + rhs.mY;

    return result;
}
*/

// 속도를 빠르게 하기위해 참조를 사용하였는데 리터럴이라 const를 붙였음
//const Point2D *this,


std::ostream& operator << (std::ostream& os, Point2D pt)
{
    os << "(" << pt.mX << "," << pt.mY << ")";
    return os;
}


int main()
{
    /*
    Point2D pt1(2, 3), pt2(3, 5);

    pt1.Print();
    pt2.Print();

    Point2D pt3 = pt1 + pt2;
    pt3.Print();
    */

    /*Point2D result = Point2D{ 2, 3 } + Point2D{3, 5};
    result.Print();*/

    /*Point2D a(2, 0), b(0, 3), c(1, 1);
    Point2D result2 = (a + b) + c;*/

    /*Point2D pt1(2, 2), pt2(2, 0);

    (pt1 + pt2).Print();
    (pt1 - pt2).Print();
    (pt1 * 3).Print();
    (pt1 / 2).Print();*/

    Point2D pt1(1, 2);

    pt1.Print();

    std::cout << pt1;
    "Test"
}