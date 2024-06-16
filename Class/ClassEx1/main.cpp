#include <iostream>

//Encapsulation

class Monster
{
private:
	int mHP;

public:
	void SetHP(int hp)
	{
		// Áö¿ªº¯¼ö ¿ì¼±
		mHP = hp;
	}
		
	int GetHP() const
	{
		return mHP;
	}
};


class Dog
{
public:

	class Toy
	{
	public:
		int color;
		void Play();
	};

	enum Breed
	{
		HUSKY,
		PUDDLE,
	};
	Breed mBreed;
public:
	void SetBreed(Breed b)
	{
		mBreed = b;
	}
};

class Cat
{
public:
	enum Breed
	{
		SHAM,
		PERSIAN,
	};

	Breed mBreed;
public:
	void SetBreed(Breed b)
	{
		mBreed = b;
	}
};

class Point2D
{
private:
	int mX;
	int mY;

public:
	void SetXY(int x, int y)
	{
		mX = x;
		mY = y;
	}

	/*int GetX() const;
	int GetY() const;*/

	void GetXY(int& x, int& y) const
	{
		x = mX;
		y = mY;
	}
};

int main()
{
	/*Monster m;
	m.SetHP(10);
	std::cout << m.GetHP() << std::endl;*/

	/*Dog d;
	d.SetBreed(Dog::Breed::HUSKY);*/

	//const Monster m{};
	//// m.SetHP(10);
	//std::cout << m.GetHP() << std::endl;

	Point2D p1;
	p1.SetXY(1, 1);

	int x, y;
	p1.GetXY(x, y);
	x = 10;
	y = 10;
	std::cout << x << "," << y << std::endl;
}
