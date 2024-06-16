#include <iostream>

/*class MyClass
{
public:
	int mX;
	float mY;

	
	// Constructor
	MyClass(){std::cout << "CONSTRUCT!" << std::endl;}

	// Destructor
	~MyClass(){std::cout << "DESTRUCT!" << std::endl;}
	
*/

class Point2D
{
private:
	int mX;
	int mY;

public:
	//Point2D() �����ڸ� �Ʒ�ó�� ������ ������ �ڵ����� �����Ǵ� �ƹ��ŵ� ���� ������
	Point2D(int x, int y)
	{
		mX = x;
		mY = y;
		std::cout << "����!" << x << "," << y << std::endl;
	}
};

class MyClass
{
public:
	int mValue1{ 10 };
	int mValue2{ 20 };

public:
	MyClass()
	{
		mValue1 = mValue2 = -1;
	}

	MyClass(int x)
	{
		mValue1 = mValue2 = x;
	}

	MyClass(int x, int y)
	{
		mValue1 = x;
		mValue2 = y;
	}
};

int main()
{
	/*
	// ������ ����� ����
	int myVariable;
	myVariable = 1;

	// �ʱ�ȭ
	float myFloat = 1.1f;
	double myDouble{ 2.0 };

	MyClass instance1;
	instance1.mX = 1;
	instance1.mY = 1.1f;
	MyClass instance2{ 1, 1.1f };
	*/

	/*int x{ 1 };

	MyClass *p = new MyClass;

	delete p;*/

	/*
	Point2D p = Point2D();
	Point2D p();
	Point2D p{};
	*/

	/*
	Point2D p = Point2D(1, 1);
	Point2D p2(2, 2);
	Point2D p3{3, 3};
	*/

	MyClass c1;
	MyClass c2(1);
	MyClass c3(2, 3);
}